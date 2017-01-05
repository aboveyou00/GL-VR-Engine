#include "stdafx.h"
#include "Program.h"
#include "Attribute.h"
#include "Snippet.h"

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

        void Program::Compile()
        {
            assert(!compilationStarted);
            compilationStarted = true;
            ResolveProperties();
            for (size_t q = 0; q < this->numComponents; q++)
            {
                if (components[q] == nullptr) continue;
                components[q]->Compile();
            }
        }

        void Program::BootstrapInputs()
        {
            assert(!compilationStarted);

        }

        void Program::ResolveProperties()
        {
            auto componentProperties = ComponentArray<std::set<ShaderProp*>>(numComponents);

            for (unsigned i = 0; i < numComponents; i++)
            {
                componentProperties[i] = std::set<ShaderProp*>();
                if (components[i] == nullptr)
                    continue;

                std::set<ShaderProp*> componentInputs = {};
                std::set<ShaderProp*> componentOutputs = {};

                for (Snippet* snippet : components[i]->unresolvedSnippets)
                    for (ShaderProp* prop : snippet->propertiesIn)
                        componentInputs.insert(prop);
                for (Snippet* snippet : components[i]->unresolvedSnippets)
                    for (ShaderProp* prop : snippet->propertiesOut)
                        componentOutputs.insert(prop);

                for (ShaderProp* prop : componentInputs)
                {
                    // property is defined within component
                    if (componentOutputs.count(prop) > 0)
                        continue;

                    // property is defined in previous component
                    for (unsigned j = i - 1; j >= 0; j--)
                    {
                        //if (componentProperties[j].count(prop) > 0)
                        //{
                        //    components[j]->outs.insert(prop);
                        //    components[i]->ins.insert(prop);
                        //    for (unsigned k = j + 1; k < i; k++)
                        //    {
                        //        components[k]->ins.insert(prop);
                        //        components[k]->outs.insert(prop);
                        //        components[k]->unresolvedSnippets.insert(Snippet::IdentitySnippet(prop));
                        //    }
                        //}
                        //goto cont;
                    }

                    // property is defined as program input

                //cont:;
                }
            }
        }

        ComponentType Program::NextComponentType(ComponentType type)
        {
            return NextComponentType((unsigned)type);
        }
        ComponentType Program::NextComponentType(unsigned type)
        {
            type = (type + 1) % numComponents;
            while (components[type] == nullptr)
                type = (type + 1) % numComponents;
            return (ComponentType)type;
        }
        ComponentType Program::LastComponentType(ComponentType type)
        {
            return LastComponentType((unsigned)type);
        }
        ComponentType Program::LastComponentType(unsigned type)
        {
            type = (type - 1 + numComponents) % numComponents;
            while (components[type] == nullptr)
                type = (type - 1 + numComponents) % numComponents;
            return (ComponentType)type;
        }
    }
}
