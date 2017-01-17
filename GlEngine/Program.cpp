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
        Program::Program(bool useTesselation, bool useGeometry)
            : components({})
        {
            components[ComponentType::Input] = new Component(ComponentType::Input);
            components[ComponentType::Output] = new Component(ComponentType::Output);

            components[ComponentType::Vertex] = new Component(ComponentType::Vertex);
            components[ComponentType::Fragment] = new Component(ComponentType::Fragment);

            if (useTesselation)
            {
                components[ComponentType::TessControl] = new Component(ComponentType::TessControl);
                components[ComponentType::TessEvaluation] = new Component(ComponentType::TessEvaluation);
            }
            if (useGeometry)
            {
                components[ComponentType::Geometry] = new Component(ComponentType::Geometry);
            }
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

        void Program::AddPropertySource(PropertySource *propSource)
        {
            assert(!compilationStarted);
            this->propSources.push_back(propSource);
        }
        void Program::AddAttribute(Attribute* attribute)
        {
            assert(!compilationStarted);
            if (std::find(addedAttributes.begin(), addedAttributes.end(), attribute) != addedAttributes.end()) return;

            auto dependents = attribute->dependentAttributes();
            for (size_t q = 0; q < dependents.size(); q++)
                AddAttribute(dependents[q]);

            for (auto type = ComponentType::Input; type <= ComponentType::Output; type++)
            {
                if (components[type] == nullptr)
                {
                    auto &snippets = attribute->snippets()[type];
                    for (size_t q = 0; q < snippets.size(); q++)
                        assert(snippets[q]->fallback());
                    continue;
                }
                for (Snippet* snippet : attribute->snippets()[type])
                    components[type]->unresolvedSnippets.insert(snippet);
            }
        }

        ShaderSource *Program::Compile()
        {
            assert(this_thread_type() == ThreadType::ResourceLoader);
            assert(!compilationStarted);
            compilationStarted = true;
            
            BootstrapInputs();
            BootstrapOutputs();

            ResolveProperties();
            auto source = new ComponentArray<std::string*>();

            for (auto type = ComponentType::Vertex; type != ComponentType::Output; type++)
            {
                if (components[type] == nullptr) continue;
                (*source)[type] = new std::string(components[type]->Compile());
                Util::Log(LogType::Info, "%s:\n%s", NameOf(type).c_str(), (*source)[type]->c_str());
            }

            return source;
        }

        void Program::BootstrapInputs()
        {
        }

        void Program::BootstrapOutputs()
        {
            components[ComponentType::Output]->unresolvedSnippets.insert(new Snippet("", { &prop_RgbaColor }, std::vector<ShaderProp*>()));
            // TODO: delete
        }

        void Program::ResolveProperties()
        {
            for (auto resolvingType = ComponentType::Vertex; resolvingType <= ComponentType::Output; resolvingType++)
            {
                if (components[resolvingType] == nullptr)
                    continue;

                while (true)
                {
                    components[resolvingType]->ResolveSnippets();
                    if (components[resolvingType]->unresolvedSnippets.size() == 0)
                        break;

                    for (ShaderProp* input : components[resolvingType]->unresolvedInputs)
                    {
                        ComponentType lookbehindType = resolvingType;
                        while (lookbehindType-- != ComponentType::Input)
                        {
                            if (components[lookbehindType] == nullptr)
                                continue;

                            auto props = components[lookbehindType]->availableLocalProps;
                            if (std::find(props.begin(), props.end(), input) != props.end())
                            {
                                ConnectComponentsProperty(lookbehindType, resolvingType, input);
                                goto found;
                            }
                        }
                        for (PropertySource* source : propSources)
                        {
                            if (source->HasProperty(input))
                            {
                                source->ProvideProperty(input, this, resolvingType);
                                goto found;
                            }
                        }
                    }

                    // CANNOT RESOLVE DEPENDENCIES
                    Util::Log(LogType::Error, "Could not resolve snippet dependencies when compiling %s shader", NameOf(resolvingType).c_str());
                    for (Snippet* snippet : components[resolvingType]->unresolvedSnippets)
                        if (!snippet->fallback())
                            components[resolvingType]->AddUnresolvedSnippet(snippet);
                    for (ShaderProp* prop : components[resolvingType]->unresolvedOutputs)
                        components[resolvingType]->availableLocalProps.insert(prop);
                    break;
                    
                found:;
                }
            }
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

            unsigned idx = uniforms.size();
            uniforms[idx] = prop;
            return idx;
        }
        void Program::ConnectComponentsProperty(ComponentType first, ComponentType last, ShaderProp *prop)
        {
            assert(first < last);
            components[first]->orderedSnippets.push_back(Snippet::IdentitySnippet(prop, false, true));
            unsigned inputIndex = components[first]->FindOrCreateOutput(prop);
            
            ComponentType currentType = first;
            while (++currentType < last)
            {
                if (components[currentType] == nullptr)
                    continue;

                components[currentType]->ins[inputIndex] = prop;
                components[currentType]->orderedSnippets.push_back(Snippet::IdentitySnippet(prop, true, true));
                inputIndex = components[currentType]->FindOrCreateOutput(prop);
            }

            components[last]->ins[inputIndex] = prop;
            components[last]->orderedSnippets.insert(components[last]->orderedSnippets.begin(), Snippet::IdentitySnippet(prop, true, false));
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
    }
}
