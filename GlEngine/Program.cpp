#include "stdafx.h"
#include "Program.h"
#include "Attribute.h"
#include "Snippet.h"
#include "ComponentType_attribs.h"
#include "LogUtils.h"
#include <fstream>
#include <direct.h>

#include "RawComponent.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Program::Program(PerformanceLevel performanceLevel)
            : components({})
        {
            SetPerformanceLevel(performanceLevel);
            //components[ComponentType::Input] = new Component(ComponentType::Input);
            //components[ComponentType::Output] = new Component(ComponentType::Output);

            //components[ComponentType::Vertex] = new Component(ComponentType::Vertex);
            //components[ComponentType::Fragment] = new Component(ComponentType::Fragment);

            //if (useTesselation)
            //{
            //    components[ComponentType::TessControl] = new Component(ComponentType::TessControl);
            //    components[ComponentType::TessEvaluation] = new Component(ComponentType::TessEvaluation);
            //}
            //if (useGeometry)
            //{
            //    components[ComponentType::Geometry] = new Component(ComponentType::Geometry);
            //}
        }

        Program::~Program()
        {
            for (auto type = ComponentType::Input; type <= ComponentType::Output; type++)
            {
                if (components[type] != nullptr)
                {
                    delete components[type];
                    components[type] = nullptr;
                }
            }
        }

        void Program::SetPerformanceLevel(PerformanceLevel performanceLevel)
        {
            assert(!compilationStarted);
            assert(performanceLevel != PerformanceLevel::Unset);

            this->performanceLevel = performanceLevel;
            if (propertyResolutionEagerness == PropertyResolutionEagerness::Unset)
            {
                switch (performanceLevel)
                {
                case PerformanceLevel::Efficient:
                    this->propertyResolutionEagerness = PropertyResolutionEagerness::Earliest;
                    break;
                case PerformanceLevel::Balanced:
                    this->propertyResolutionEagerness = PropertyResolutionEagerness::Default;
                    break;
                case PerformanceLevel::Accurate:
                    this->propertyResolutionEagerness = PropertyResolutionEagerness::Latest;
                }
            }
        }

        void Program::SetPropertyResolutionEagerness(PropertyResolutionEagerness eagerness)
        {
            assert(!compilationStarted);
            assert(eagerness != PropertyResolutionEagerness::Unset);
            propertyResolutionEagerness = eagerness;
        }

        void Program::AddPropertySource(PropertySource *propSource)
        {
            assert(!compilationStarted);
            this->propertySources.push_back(propSource);
        }
        void Program::AddAttribute(Attribute* attribute)
        {
            AddAttributeInternal(attribute, 0);
        }

        ShaderSource *Program::Compile()
        {
            assert(!compilationStarted);
            compilationStarted = true;
            
            SetDefaultFlags();
            BuildDependencyTree();

            auto source = new ComponentArray<std::string*>();
            for (auto type = ComponentType::Vertex; type != ComponentType::Output; type++)
            {
                if (components[type] == nullptr) continue;
                (*source)[type] = new std::string(components[type]->Compile());
                Util::Log(LogType::Info, "%s:\n%s", NameOf(type).c_str(), (*source)[type]->c_str());
            }
            return source;
        }

        void Program::SetDefaultFlags()
        {
            if (performanceLevel == PerformanceLevel::Unset)
                SetPerformanceLevel(PerformanceLevel::Balanced);
        }

        //int Program::FindUniform(ShaderProp *prop)
        //{
        //    for (auto it : uniforms)
        //        if (it.second == prop)
        //            return it.first;
        //    return -1;
        //}
        //unsigned Program::FindOrCreateUniform(ShaderProp *prop)
        //{
        //    auto location = FindUniform(prop);
        //    if (location != -1) return static_cast<unsigned>(location);

        //    unsigned idx = uniforms.size();
        //    uniforms[idx] = prop;
        //    return idx;
        //}
        void Program::ConnectComponentsProperty(ComponentType first, ComponentType last, ShaderProp *prop)
        {
            assert(first < last);
            components[first]->snippets.push_back(Snippet::IdentitySnippet(prop, false, true));
            unsigned inputIndex = components[first]->FindOrCreateOutput(prop);
            
            ComponentType currentType = first;
            while (++currentType < last)
            {
                if (components[currentType] == nullptr)
                    continue;

                components[currentType]->ins[inputIndex] = prop;
                components[currentType]->snippets.push_back(Snippet::IdentitySnippet(prop, true, true));
                inputIndex = components[currentType]->FindOrCreateOutput(prop);
            }

            components[last]->ins[inputIndex] = prop;
            components[last]->snippets.insert(components[last]->snippets.begin(), Snippet::IdentitySnippet(prop, true, false));
        }

        void Program::WriteToDisk(std::string name)
        {
            assert(name.length() > 0);
            _mkdir("generated_shader");
            for (auto type = ComponentType::Vertex; type != ComponentType::Output; type++)
            {
                if (type == ComponentType::Input || type == ComponentType::Output || components[type] == nullptr)
                    continue;
                std::ofstream outFile;
                outFile.open("generated_shader/" + name + "." + NameOf(type) + ".shader");
                outFile << components[type]->compiled;
                outFile.close();
            }
        }

        size_t Program::AddAttributeInternal(Attribute* attribute, size_t earliest)
        {
            assert(!compilationStarted);
            auto dependents = attribute->dependentAttributes();
            
            size_t origSize = attributes.size();
            size_t lastPos = 0;
            
            for (size_t q = 0; q < dependents.size(); q++)
            {
                size_t pos = AddAttributeInternal(dependents[q], lastPos);
                if (pos < lastPos)
                {
                    error = ShaderFactoryError::AttributeDependencyError;
                    Util::Log(LogType::ErrorC, "Could not resolve attribute dependencies in ShaderFactory::Program");
                }
                lastPos = pos;
            }
            earliest = max(earliest + attributes.size() - origSize, lastPos);

            auto attributePos = std::find(attributes.begin(), attributes.end(), attribute) - attributes.begin();
            if (attributePos < earliest)
            {
                error = ShaderFactoryError::AttributeDependencyError;
                Util::Log(LogType::ErrorC, "Could not resolve attribute dependencies in ShaderFactory::Program");
            }

            if (attributePos == attributes.size())
            {
                attributes.insert(attributes.begin() + earliest, attribute);
                return earliest;
            }
            else
                return attributePos;
        }

        ComponentType Program::latest(std::vector<ComponentType> components)
        {
            ComponentType result = components[0];
            for (size_t i = 1; i < components.size(); i++)
                if (components[i] > result)
                    result = components[i];
            return result;
        }

        ComponentType Program::earliest(std::vector<ComponentType> components)
        {
            ComponentType result = components[0];
            for (size_t i = 1; i < components.size(); i++)
                if (components[i] < result)
                    result = components[i];
            return result;
        }

        std::vector<ComponentType> Program::orderedComponents(PropertySource * source)
        {
            switch (propertyResolutionEagerness)
            {
            case PropertyResolutionEagerness::Earliest:
                return source->componentsEarliest();
            case PropertyResolutionEagerness::Latest:
                return source->componentsLatest();
            case PropertyResolutionEagerness::Default:
                return source->componentsDefault();
            }
            assert(false);
        }

        std::map<PropertySource*, std::vector<ComponentType>> Program::sourceConstraints()
        {
            std::map<PropertySource*, std::vector<ComponentType>> result;
            for (auto pair : propertySourceInputs)
                result[pair.first] = orderedComponents(pair.first);

            for (auto pair : result)
            {
                auto constraintLatest = latest(pair.second);
                for (auto input : propertySourceInputs[pair.first])
                {
                    std::vector<ComponentType> inputConstraints = result[input];
                    auto inputConstraintEarliest = earliest(inputConstraints);
                    
                    for (auto it = pair.second.begin(); it != pair.second.end(); it++)
                        if (*it < inputConstraintEarliest)
                            pair.second.erase(it);
                    for (auto it = inputConstraints.begin(); it != inputConstraints.end(); it++)
                        if (*it > constraintLatest)
                            inputConstraints.erase(it);
                }
            }
            return result;
        }

        std::set<std::pair<ShaderProp*, PropertySource*>> Program::unresolvedProperties()
        {
            std::set<std::pair<ShaderProp*, PropertySource*>> unresolvedProperties;
            for (auto pair : propertySourceInputs)
            {
                auto inProperties = pair.first->inProperties();
                for (int i = 0; i < inProperties.size(); i++)
                    if (pair.second[i] == nullptr)
                        unresolvedProperties.insert({ inProperties[i], pair.first });
            }
            return unresolvedProperties;
        }

        std::vector<PropertySource*> Program::sourceDependencies(PropertySource* source, std::vector<PropertySource*> dependencySources)
        {
            for (ShaderProp* dependency : source->inProperties())
            {
                auto pos = currentPropertySources.find(dependency);
                if (pos == currentPropertySources.end())
                    dependencySources.push_back(nullptr);
                else
                    dependencySources.push_back(pos->second);
            }
            return dependencySources;
        }

        bool Program::sourceDependenciesMet(PropertySource* source, std::vector<PropertySource*> dependencySources)
        {
            for (ShaderProp* dependency : source->inProperties())
            {
                auto pos = currentPropertySources.find(dependency);
                if (pos == currentPropertySources.end())
                    return false;
                else
                    dependencySources.push_back(pos->second);
            }
            return true;
        }

        void Program::AddToDependencyTree(PropertySource* source, std::vector<PropertySource*> dependencies)
        {
            for (ShaderProp* prop : source->outProperties())
                currentPropertySources[prop] = source;

            propertySourceInputs[source] = dependencies;
            propertySourceOutputs[source] = {};
            for (PropertySource* dependency : dependencies)
                if (dependency != nullptr)
                    propertySourceOutputs[dependency].push_back(source);
        }

        void Program::ResolveAttributeDependencies(Attribute* attribute)
        {
            std::vector<PropertySource*> unresolvedSources;
            for (PropertySource* source : attribute->propertySources())
                unresolvedSources.push_back(source);

            bool changed = true;
            std::vector<PropertySource*> dependencySources;
            while (changed)
            {
                changed = false;
                for (auto ptr = unresolvedSources.begin(); ptr != unresolvedSources.end(); ptr++)
                {
                    PropertySource* source = *ptr;
                    dependencySources.clear();
                    if (sourceDependenciesMet(source, dependencySources))
                    {
                        AddToDependencyTree(source, dependencySources);
                        unresolvedSources.erase(ptr);
                        changed = true;
                        break;
                    }
                }
            }

            for (PropertySource* source : unresolvedSources)
            {
                AddToDependencyTree(source, sourceDependencies(source));
            }
        }

        bool Program::TryResolveComponents(std::map<PropertySource*, std::vector<ComponentType>> constraints)
        {
            std::map<PropertySource*, size_t> assignedComponents;
            
            auto it = propertySourceInputs.begin();
            while (it != propertySourceInputs.end())
            {
                ComponentType early = ComponentType::Vertex;
                for (PropertySource* input : it->second)
                {
                    if (assignedComponents.find(input) != assignedComponents.end())
                        early = max(early, constraints[input][assignedComponents[input]]);
                    else
                        early = max(early, earliest(constraints[input]));
                }

                size_t componentIndex = (assignedComponents.find(it->first) != assignedComponents.end()) ? assignedComponents[it->first] + 1 : 0;
                for (; componentIndex < constraints[it->first].size(); componentIndex++)
                    if (constraints[it->first][componentIndex] >= early)
                        break;

                if (componentIndex == constraints[it->first].size())
                {
                    if (it == propertySourceInputs.begin())
                        return false;
                    assignedComponents.erase(it->first);
                    it--;
                }
                else
                {
                    assignedComponents[it->first] = componentIndex;
                    it++;
                }
            }

            for (auto pair : propertySourceInputs)
            {
                pair.first
            }
        }

        void Program::ResolveFallbacks()
        {
            auto constraints = sourceConstraints();
            auto unresolvedProps = unresolvedProperties();

            size_t lastSize = 0;
            while (unresolvedProps.size() != lastSize)
            {
                for (PropertySource* fallback : fallbackSources)
                {
                    ShaderProp* prop = fallback->outProperties()[0];
                    if (unresolvedProps.find(prop) != unresolvedProps.end() && u)
                    {

                    }
                }
            }

            if (unresolvedProperties.size() > 0)
            {
                Util::Log(LogType::ErrorC, "Could not resolve properties in Program compilation");
                // TODO: more info, set error
            }
        }

        void Program::BuildDependencyTree()
        {
            for (PropertySource* source : propertySources)
                AddToDependencyTree(source, {});

            for (Attribute* attribute : attributes)
            {
                fallbackSources.insert(fallbackSources.begin(), attribute->fallbackSources().begin(), attribute->fallbackSources().end());
                ResolveAttributeDependencies(attribute);
            }
            ResolveFallbacks();
        }
    }
}
