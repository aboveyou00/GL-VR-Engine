#include "stdafx.h"
#include "Component.h"
#include "ComponentType_attribs.h"

#include "StringUtils.h"
#include "LogUtils.h"

#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Component::Component(ComponentType type)
            : type(type), ins({}), outs({}), unresolvedInputs({}), availableLocalProps({}), unresolvedOutputs({}), unresolvedSnippets({})
        {
        }
        Component::~Component()
        {
        }

        bool Component::ResolveSnippets()
        {
            for (auto it: ins)
                addLocalProp(it.second);

            unsigned last_size = 0;
            bool changed = false;
            while (unresolvedSnippets.size() > 0)
            {
                if (unresolvedSnippets.size() == last_size)
                    break;

                for (Snippet* snippet : unresolvedSnippets)
                {
                    if (snippetDependenciesMet(snippet))
                    {
                        orderedSnippets.push_back(snippet);
                        unresolvedSnippets.erase(snippet);
                        for (ShaderProp* prop : snippet->propertiesOut)
                            addLocalProp(prop);
                        changed = true;
                    }
                }
            }
            unresolvedOutputs.clear();
            unresolvedInputs.clear();
            for (Snippet* snippet : unresolvedSnippets)
            {
                for (size_t q = 0; q < snippet->propertiesIn.size(); q++)
                    unresolvedInputs.insert(snippet->propertiesIn[q]);
                for (size_t q = 0; q < snippet->propertiesOut.size(); q++)
                    unresolvedOutputs.insert(snippet->propertiesOut[q]);
            }
            return changed;
        }
        bool Component::IsResolved()
        {
            return unresolvedSnippets.size() == 0;
        }

        bool Component::snippetDependenciesMet(Snippet* snippet)
        {
            for (ShaderProp* prop : snippet->propertiesIn)
                if (std::find(availableLocalProps.begin(), availableLocalProps.end(), prop) == availableLocalProps.end())
                    return false;
            return true;
        }
        void Component::addLocalProp(ShaderProp *prop)
        {
            if (std::find(availableLocalProps.begin(), availableLocalProps.end(), prop) == availableLocalProps.end())
                availableLocalProps.insert(prop);
        }

        unsigned Component::FindOrCreateOutput(ShaderProp * prop)
        {
            for (auto it : outs)
                if (it.second == prop)
                    return it.first;
            unsigned idx = outs.size();
            outs[idx] = prop;
            return idx;
        }

        std::string Component::Compile()
        {
            std::string result = "";
            result += compileVersion() + "\n";
            result += compileLayouts() + "\n";
            result += compileDecl() + "\n";
            result += "void main(void) {\n" + compileMain() + "\n}\n";
            
            compiled = result;
            return result;
        }

        std::string Component::compileVersion()
        {
            return "#version 430";
        }

        std::string Component::compileLayouts()
        {
            std::string result = "";
            
            for (auto it : uniforms)
                result += Util::formatted("layout(location = %i) uniform %s;\n", it.first, it.second->DeclarationString("in_"));
            result += "\n";
            for (auto it : ins)
                result += Util::formatted("layout(location = %i) in %s;\n", it.first, it.second->DeclarationString("in_"));
            result += "\n";
            for (auto it : outs)
                result += Util::formatted("layout(location = %i) out %s;\n", it.first, it.second->DeclarationString("out_"));

            return result;
        }

        std::string Component::compileDecl()
        {
            std::string result = "";
            for (Snippet* snippet : orderedSnippets)
                result += snippet->declSource + "\n";
            return result;
        }

        std::string Component::compileMain()
        {            
            std::string result;
            for (Snippet* snippet : orderedSnippets)
                result += snippet->mainSource + "\n";
            return result;
        }
    }
}
