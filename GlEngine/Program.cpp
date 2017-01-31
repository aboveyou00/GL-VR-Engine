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
            : components({}), performanceLevel(PerformanceLevel::Unset), propertyResolutionEagerness(PropertyResolutionEagerness::Unset)
        {
            if (performanceLevel != PerformanceLevel::Unset)
                SetPerformanceLevel(performanceLevel);
            
            components[ComponentType::Input] = new Component(ComponentType::Input);
            components[ComponentType::Output] = new Component(ComponentType::Output);

            components[ComponentType::Vertex] = new Component(ComponentType::Vertex);
            components[ComponentType::Fragment] = new Component(ComponentType::Fragment);

            components[ComponentType::TessControl] = new Component(ComponentType::TessControl);
            components[ComponentType::TessEvaluation] = new Component(ComponentType::TessEvaluation);
            
            components[ComponentType::Geometry] = new Component(ComponentType::Geometry);

            AddAttribute(&attr_OutColor);
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
            assert(this_thread_type() == ThreadType::ResourceLoader);
            assert(!compilationStarted);
            SetDefaultFlags();
            compilationStarted = true;
            
            BuildDependencyTree();
            
            ComponentArray<bool> usedComponents;
            for (ComponentType type = ComponentType::Input; type <= ComponentType::Output; type++)
            {
                usedComponents[type] = false;
                for (PropertySource* source : componentSources[type])
                {
                    source->Inject(this, type);
                    usedComponents[type] = true;
                }
            }
            usedComponents[ComponentType::Vertex] = true;
            usedComponents[ComponentType::Fragment] = true;

            auto source = new ComponentArray<std::string*>();
            for (auto type = ComponentType::Vertex; type != ComponentType::Output; type++)
            {
                if (!usedComponents[type])
                    continue;
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

        int Program::FindUniform(ShaderProp *prop)
        {
            for (auto it : uniforms)
                if (it.second == prop)
                    return it.first;
            return -1;
        }
        unsigned Program::FindOrCreateUniform(ShaderProp *prop)
        {
            auto location = FindUniform(prop);
            if (location != -1) return static_cast<unsigned>(location);

            unsigned idx = nextUniformIdx;
            uniforms[idx] = prop;
            nextUniformIdx += prop->layoutSize();
            return idx;
        }

        void Program::ConnectComponentsProperty(ComponentType first, ComponentType last, ShaderProp *prop)
        {
            assert(first < last);
            components[first]->AddIdentitySnippet(prop, false, true);
            unsigned inputIndex = components[first]->FindOrCreateOutput(prop);
            
            ComponentType currentType = first;
            while (++currentType < last)
            {
                if (components[currentType] == nullptr)
                    continue;

                components[currentType]->ins[inputIndex] = prop;
                components[currentType]->AddIdentitySnippet(prop, true, true);
                inputIndex = components[currentType]->FindOrCreateOutput(prop);
            }

            components[last]->ins[inputIndex] = prop;
            components[last]->AddIdentitySnippet(prop, true, false);
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

        int Program::AddAttributeInternal(Attribute* attribute, int earliest)
        {
            assert(!compilationStarted);
            auto dependents = attribute->dependentAttributes();
            
            int origSize = attributes.size();
            int lastPos = -1;
            
            for (size_t q = 0; q < dependents.size(); q++)
            {
                int pos = AddAttributeInternal(dependents[q], lastPos + 1);
                if (pos < lastPos)
                {
                    error = ShaderFactoryError::AttributeDependencyError;
                    Util::Log(LogType::ErrorC, "Could not resolve attribute dependencies in ShaderFactory::Program");
                }
                else
                    lastPos = pos;
            }
            earliest = max(earliest + (int)attributes.size() - origSize, lastPos + 1);

            int attributePos = std::find(attributes.begin(), attributes.end(), attribute) - attributes.begin();
            if (attributePos < earliest)
            {
                error = ShaderFactoryError::AttributeDependencyError;
                Util::Log(LogType::ErrorC, "Could not resolve attribute dependencies in ShaderFactory::Program");
            }

            if (attributePos == (int)attributes.size())
            {
                attributes.insert(attributes.begin() + earliest, attribute);
                return earliest;
            }
            else
                return attributePos;
        }

        ComponentType Program::latestComponent(std::vector<ComponentType> components)
        {
            ComponentType result = components[0];
            for (size_t i = 1; i < components.size(); i++)
                if (components[i] > result)
                    result = components[i];
            return result;
        }

        ComponentType Program::earliestComponent(std::vector<ComponentType> components)
        {
            ComponentType result = components[0];
            for (size_t i = 1; i < components.size(); i++)
                if (components[i] < result)
                    result = components[i];
            return result;
        }

        std::vector<ComponentType> Program::orderedComponents(PropertySource *source)
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
            __assume(false);
        }

        void Program::CalculateConstraints()
        {
            constraints.clear();

            for (auto pair : propertySourceInputs)
                constraints[pair.first] = orderedComponents(pair.first);

            for (auto pair : constraints)
            {
                auto constraintLatest = latestComponent(pair.second);
                for (auto input : propertySourceInputs[pair.first])
                {
                    if (input == nullptr)
                        continue;
                    if (input == PropertySource::resolvedPropertySource)
                        continue;

                    std::vector<ComponentType> inputConstraints = constraints[input];
                    auto inputConstraintEarliest = earliestComponent(inputConstraints);

                    for (auto it = pair.second.begin(); it != pair.second.end(); )
                    {
                        if (*it < inputConstraintEarliest) it = pair.second.erase(it);
                        else it++;
                    }
                    size_t i = 0;
                    while (i < inputConstraints.size())
                    {
                        if (inputConstraints[i] > constraintLatest)
                            inputConstraints.erase(inputConstraints.begin() + i);
                        else
                            i++;
                    }
                }
            }
        }

        std::map<ShaderProp*, std::set<PropertySource*>> Program::unresolvedProperties()
        {
            std::map<ShaderProp*, std::set<PropertySource*>> result;
            for (PropertySource* source : allSources)
            {
                auto inProperties = source->inProperties();
                for (size_t i = 0; i < inProperties.size(); i++)
                {
                    if (propertySourceInputs[source][i] == nullptr)
                    {
                        if (result.find(inProperties[i]) == result.end())
                            result[inProperties[i]] = {};
                        result[inProperties[i]].insert(source);
                    }
                }
            }
            return result;
        }

        std::map<ShaderProp*, std::vector<PropertySource*>> Program::propertyFallbacks()
        {
            std::map<ShaderProp*, std::vector<PropertySource*>> result;
            for (PropertySource* fallback : fallbackSources)
            {
                auto prop = fallback->outProperties()[0];
                if (result.find(prop) == result.end())
                    result[fallback->outProperties()[0]] = {};
                result[fallback->outProperties()[0]].push_back(fallback);
            }
            return result;
        }

        bool Program::isEventualChild(PropertySource* parent, PropertySource* child)
        {
            return isEventualChild(std::set<PropertySource*>{ parent }, std::set<PropertySource*>{ child });
        }
        bool Program::isEventualChild(std::set<PropertySource*> parents, std::set<PropertySource*> children)
        {
            std::set<PropertySource*> level = children;
            while (level.size() > 0)
            {
                std::set<PropertySource*> newLevel;
                for (auto source : level)
                {
                    if (parents.find(source) != parents.end())
                        return true;
                    newLevel.insert(propertySourceDependents[source].begin(), propertySourceDependents[source].end());
                }
                level = newLevel;
            }
            return false;
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

        bool Program::SourceDependenciesMet(PropertySource* source, std::vector<PropertySource*> &dependencySources)
        {
            for (ShaderProp* dependency : source->inProperties())
            {
                if (dependency->hasFlag(PropertyFlag::Resolved))
                {
                    dependencySources.push_back(PropertySource::resolvedPropertySource);
                }
                else
                {
                    auto pos = currentPropertySources.find(dependency);
                    if (pos == currentPropertySources.end())
                        return false;
                    else
                        dependencySources.push_back(pos->second);
                }
            }
            return true;
        }

        void Program::AddToDependencyTree(PropertySource* source, std::vector<PropertySource*> dependencies)
        {
            allSources.push_back(source);
            for (ShaderProp* prop : source->outProperties())
            {
                currentPropertySources[prop] = source;
                if (allPropertySources.find(prop) == allPropertySources.end())
                    allPropertySources[prop] = {};
                allPropertySources[prop].push_back(source);
            }

            propertySourceInputs[source] = dependencies;
            propertySourceDependents[source] = {};
            for (PropertySource* dependency : dependencies)
                if (dependency != nullptr)
                    propertySourceDependents[dependency].push_back(source);
        }

        void Program::AddFallbackToDependencyTree(PropertySource* fallback, std::set<PropertySource*> outputs, std::map<PropertySource*, std::vector<ComponentType>> constraints, std::map<PropertySource*, std::vector<ComponentType>> newConstraints)
        {
            newConstraints.clear();
            for (auto pair : constraints)
            {
                std::vector<ComponentType> sourceConstraints;
                sourceConstraints.insert(sourceConstraints.begin(), pair.second.begin(), pair.second.end());
                newConstraints[pair.first] = sourceConstraints;
            }

            auto prop = fallback->outProperties()[0];
            ComponentType parentLatest = ComponentType::Fragment;

            propertySourceDependents[fallback] = {};
            for (auto output : outputs)
            {
                size_t inputPos = std::find(output->inProperties().begin(), output->inProperties().end(), prop) - output->inProperties().begin();
                propertySourceInputs[output][inputPos] = fallback;
                propertySourceDependents[fallback].push_back(output);
                
                parentLatest = max(parentLatest, latestComponent(constraints[output]));
            }
            
            propertySourceInputs[fallback] = {};
            for (auto inProp : fallback->inProperties())
            {
                auto childPtr = allPropertySources[inProp].begin();
                PropertySource* child;
                // These defaults will never be used, I am guaranteeing to the compiler they are initialized
                ComponentType fallbackEarliest = ComponentType::Input;
                ComponentType fallbackLatest = ComponentType::Input;
                ComponentType childEarliest = ComponentType::Input;

                for (; childPtr != allPropertySources[inProp].end(); childPtr++)
                {
                    child = *childPtr;
                    fallbackEarliest = earliestComponent(fallback->componentsDefault());
                    fallbackLatest = latestComponent(fallback->componentsDefault());
                    childEarliest = earliestComponent(constraints[child]);

                    if (childEarliest <= fallbackLatest && fallbackEarliest <= parentLatest && !isEventualChild({ child }, outputs))
                        break;
                }

                if (childPtr == allPropertySources[inProp].end())
                {
                    propertySourceInputs[fallback].push_back(nullptr);
                }
                else
                {
                    propertySourceDependents[child].push_back(fallback);
                    propertySourceInputs[fallback].push_back(child);

                    newConstraints[fallback] = std::vector<ComponentType>();
                    for (auto c : fallback->componentsDefault())
                        if (childEarliest <= c && c <= parentLatest)
                            newConstraints[fallback].push_back(c);
                    for (auto cPtr = constraints[child].begin(); cPtr != constraints[child].end(); cPtr++)
                        if (*cPtr > fallbackLatest)
                            newConstraints[child].erase(cPtr - constraints[child].begin() + newConstraints[child].begin());
                    for (auto parent : outputs)
                        for (auto cPtr = constraints[parent].begin(); cPtr != constraints[child].end(); cPtr++)
                            if (*cPtr < fallbackEarliest)
                                newConstraints[parent].erase(cPtr - constraints[parent].begin() + newConstraints[parent].begin());
                }
            }
        }

        void Program::RemoveFallbackFromDependencyTree(PropertySource* fallback)
        {
            auto inputs = propertySourceInputs.find(fallback);
            if (inputs != propertySourceInputs.end())
            {
                for (auto input : inputs->second)
                {
                    auto fallbackPtr = std::find(propertySourceDependents[input].begin(), propertySourceDependents[input].end(), fallback);
                    if (fallbackPtr != propertySourceDependents[input].end())
                        propertySourceDependents[input].erase(fallbackPtr);
                }
                propertySourceInputs.erase(inputs);
            }
            auto outputs = propertySourceDependents.find(fallback);
            if (outputs != propertySourceDependents.end())
            {
                for (auto output : outputs->second)
                {
                    auto fallbackPtr = std::find(propertySourceInputs[output].begin(), propertySourceInputs[output].end(), fallback);
                    if (fallbackPtr != propertySourceInputs[output].end())
                        propertySourceInputs[output].erase(fallbackPtr);
                }
                propertySourceDependents.erase(outputs);
            }
        }

        bool Program::FindFallback(ShaderProp * prop, std::map<ShaderProp*, std::set<PropertySource*>> unresolvedProps, std::map<ShaderProp*, std::vector<PropertySource*>> propFallbacks, std::map<PropertySource*, std::vector<ComponentType>> currentConstraints, std::map<PropertySource*, std::vector<ComponentType>> newConstraints)
        {    
            for (auto fallback : propFallbacks[prop])
            {
                newConstraints.clear();
                for (auto pair : constraints)
                {
                    std::vector<ComponentType> sourceConstraints;
                    sourceConstraints.insert(sourceConstraints.begin(), pair.second.begin(), pair.second.end());
                    newConstraints[pair.first] = sourceConstraints;
                }

                AddFallbackToDependencyTree(fallback, unresolvedProps[prop], currentConstraints, newConstraints);
                size_t i = 0;
                for (; i < fallback->inProperties().size(); i++)
                {
                    std::map<PropertySource*, std::vector<ComponentType>> foundConstraints;
                    if (propertySourceInputs[fallback][i] == nullptr)
                        if (!FindFallback(fallback->inProperties()[i], unresolvedProps, propFallbacks, newConstraints, foundConstraints))
                            break;
                    newConstraints = foundConstraints;
                }
                if (i == fallback->inProperties().size())
                    return true;
                RemoveFallbackFromDependencyTree(fallback);
            }
            
            return false;
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
                    if (SourceDependenciesMet(source, dependencySources))
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

        void Program::ResolveComponents()
        {
            std::map<PropertySource*, size_t> assignedComponents;
            
            for (auto source : allSources)
            {
                ComponentType early = ComponentType::Vertex;
                for (PropertySource* input : propertySourceInputs[source])
                {
                    assert(input != nullptr);
                    if (input == PropertySource::resolvedPropertySource)
                        early = early;
                    else if (assignedComponents.find(input) != assignedComponents.end())
                        early = max(early, constraints[input][assignedComponents[input]]);
                    else
                        early = max(early, earliestComponent(constraints[input]));
                }

                size_t componentIndex = (assignedComponents.find(source) != assignedComponents.end()) ? assignedComponents[source] + 1 : 0;
                for (; componentIndex < constraints[source].size(); componentIndex++)
                    if (constraints[source][componentIndex] >= early)
                        break;
                
                assignedComponents[source] = componentIndex;
                sourceComponents[source] = constraints[source][componentIndex];
                componentSources[constraints[source][componentIndex]].push_back(source);
            }
        }

        bool Program::ResolveFallbacks()
        {
            CalculateConstraints();
            auto unresolvedProps = unresolvedProperties();
            auto propFallbacks = propertyFallbacks();
            
            for (auto source : allSources)
            {
                for (size_t i = 0; i < propertySourceInputs[source].size(); i++)
                {
                    if (propertySourceInputs[source][i] == nullptr)
                    {
                        ShaderProp* prop = source->inProperties()[i];
                        auto fallbacksPtr = propFallbacks.find(prop);
                        std::map<PropertySource*, std::vector<ComponentType>> newConstraints;
                        if (fallbacksPtr == propFallbacks.end() || !FindFallback(prop, unresolvedProps, propFallbacks, constraints, newConstraints))
                        {
                            Util::Log(LogType::ErrorC, "Could not resolve properties in Program compilation");
                            // TODO: more info, set error
                            return false;
                        }
                        constraints = newConstraints;
                    }
                }
            }
            return true;
        }

        void Program::BuildDependencyTree()
        {
            for (PropertySource* source : propertySources)
                AddToDependencyTree(source, {});

            for (Attribute* attribute : attributes)
            {
                auto attributeFallbacks = attribute->fallbackSources();
                fallbackSources.insert(fallbackSources.begin(), attributeFallbacks.begin(), attributeFallbacks.end());
                ResolveAttributeDependencies(attribute);
            }
            
            //ResolveFallbacks();
            CalculateConstraints();
            ResolveComponents();
        }
    }
}
