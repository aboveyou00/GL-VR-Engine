#include "stdafx.h"
#include "Program.h"
#include "Attribute.h"
#include "Snippet.h"
#include "ComponentType_attribs.h"
#include <fstream>
#include <direct.h>

namespace GlEngine
{
    namespace ShaderFactory
    {
        Program::Program(bool useTesselation, bool useGeometry)
            : components(numComponents)
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
            for (unsigned i = 0; i < numComponents; i++)
            {
                if (components[i] != nullptr)
                    delete components[i];
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
            for (unsigned i = 0; i < attribute->numComponents; i++)
            {
                if (components[i] == nullptr)
                {
                    assert(attribute->snippets[i].size() == 0);
                    continue;
                }
                for (Snippet snippet : attribute->snippets[i])
                    components[i]->unresolvedSnippets.insert(&snippet);
            }
        }

        void Program::Compile(bool writeToDisk)
        {
            assert(!compilationStarted);
            compilationStarted = true;
            ResolveProperties();
            for (size_t q = 0; q < this->numComponents; q++)
            {
                if (components[q] == nullptr) continue;
                components[q]->Compile();
            }

            if (writeToDisk)
                WriteToDisk();
        }

        void Program::BootstrapInputs()
        {
            assert(!compilationStarted);
        }

        void Program::BootstrapOutputs()
        {
            assert(!compilationStarted);
            components[ComponentType::Output]->unresolvedSnippets.insert(new Snippet("", { &prop_RgbaColor }, std::vector<ShaderProp*>()));
            // TODO: delete
        }

        void Program::ResolveProperties()
        {
            for (unsigned i = 0; i < numComponents; i++)
            {
                if (components[i] == nullptr)
                    continue;

                while (true)
                {
                    bool changed = components[i]->ResolveSnippets();
                    if (components[i]->unresolvedSnippets.size() == 0)
                        break;

                    if (!changed)
                    {
                        Util::Log(LogType::Error, "Could not resolve dependencies when compiling %s shader; enable level logging 'info' to view snippet data", NameOf((ComponentType)i));
                        for (Snippet* snippet : components[i]->unresolvedSnippets)
                            Util::Log(LogType::Info, "\nSnippetDecl:\n%s\nSnippet Main:\n%s", snippet->declSource, snippet->mainSource);
                        
                        for (ShaderProp* prop : components[i]->unresolvedOutputs)
                            components[i]->availableLocalProps.insert(prop);
                        break;
                    }

                    for (ShaderProp* input : components[i]->unresolvedInputs)
                    {
                        for (unsigned j = i - 1; j >= 0; j--)
                        {
                            auto props = components[j]->availableLocalProps;
                            if (std::find(props.begin(), props.end(), input) != props.end())
                            {
                                ConnectComponentsProperty(j, i, input);
                                goto found;
                            }
                        }
                        for (PropertySource* source : propSources)
                        {
                            if (source->HasProperty(input))
                            {
                                source->ProvideProperty(input, this, (ComponentType)i);
                                goto found;
                            }
                        }
                    }
                    found:;
                }
            }
        }

        void Program::ConnectComponentsProperty(unsigned firstIndex, unsigned lastIndex, ShaderProp * prop)
        {
            components[firstIndex]->orderedSnippets.push_back(Snippet::IdentitySnippet(prop, false, true));
            unsigned idx = components[firstIndex]->FindOrCreateOutput(prop);
            for (unsigned i = firstIndex + 1; i < lastIndex; i++)
            {
                components[i]->ins[idx] = prop;
                components[i]->orderedSnippets.push_back(Snippet::IdentitySnippet(prop, true, true));
                idx = components[i]->FindOrCreateOutput(prop);
            }
            components[lastIndex]->ins[idx] = prop;
            components[lastIndex]->orderedSnippets.insert(components[lastIndex]->orderedSnippets.begin(), Snippet::IdentitySnippet(prop, true, false));
        }

        unsigned Program::FindOrCreateUniform(ShaderProp * prop)
        {
            for (auto it : uniforms)
                if (it.second == prop)
                    return it.first;
            unsigned idx = uniforms.size();
            uniforms[idx] = prop;
            return idx;
        }

        void Program::WriteToDisk()
        {
            _mkdir("shader");
            for (unsigned i = 0; i < numComponents; i++)
            {
                ComponentType type = (ComponentType)i;
                if (type == ComponentType::Input || type == ComponentType::Output || components[type] == nullptr)
                    continue;
                std::ofstream outFile;
                outFile.open("shader/" + NameOf(type) + ".shader");
                outFile << components[type]->compiled;
                outFile.close();
            }
        }
    }
}