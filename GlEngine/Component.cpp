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
            for (ShaderProp* prop : ins)
                addLocalProp(prop);
            unsigned last_size = 0;
            bool changed = false;
            while (unresolvedSnippets.size() > 0)
            {
                if (unresolvedSnippets.size() == last_size) break;
                //{
                //    Util::Log(LogType::Error, "Circular snippet dependencies detected when compiling %s shader; enable level logging 'info' to view snippet data", ComponentTypeName(type));
                //    for (Snippet* snippet : unresolvedSnippets)
                //        Util::Log(LogType::Info, "\nSnippet Data:\n%s", snippet->source);
                //    return false;
                //}

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
            {
                if (std::find(availableLocalProps.begin(), availableLocalProps.end(), prop) == availableLocalProps.end())
                    return false;
            }
            return true;
        }
        void Component::addLocalProp(ShaderProp *prop)
        {
            if (std::find(availableLocalProps.begin(), availableLocalProps.end(), prop) == availableLocalProps.end())
                availableLocalProps.insert(prop);
        }

        std::string Component::Compile()
        {
            std::string result = "";
            result += compileVersion() + "\n";
            result += compileLayouts() + "\n";
            result += compileBody() + "\n";
            result += "void main(void){\n" + compileSource() + "\n}\n";
            
            return result;
        }

        std::string Component::compileVersion()
        {
            return "#version 430";
        }

        std::string Component::compileLayouts()
        {
            std::string result = "";
            
            //int count = 0;
            //for (Property* property : uniforms)
            //    result += Util::formatted("layout(location = %i) uniform %s;\n", count++, property->DeclerationString());
            //count = 0; result += "\n";
            //for (Property* property : ins)
            //    result += Util::formatted("layout(location = %i) in %s;\n", count++, property->DeclerationString("in_"));
            //count = 0; result += "\n";
            //for (Property* property : outs)
            //    result += Util::formatted("layout(location = %i) out %s;\n", count++, property->DeclerationString("out_"));

            return result;
        }

        std::string Component::compileBody()
        {
            std::string result = "";
            for (Snippet* snippet : unresolvedSnippets)
                result += snippet->declSource + "\n";
            return result;
        }

        std::string Component::compileSource()
        {
            //CreateConstantsSnippet();
            //if (!ResolveSnippetOrder())
            //    return "";
            
            std::string result;
            for (Snippet* snippet : orderedSnippets)
                result += snippet->mainSource + "\n";
            return result;
        }
    }
}
