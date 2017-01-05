#include "stdafx.h"
#include "Component.h"

#include "StringUtils.h"
#include "LogUtils.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Component::Component(ComponentType type)
            : type(type)
        {
        }
        Component::~Component()
        {
            if (constantsSnippet != nullptr)
                delete constantsSnippet;
        }

        std::string Component::Compile()
        {
			ResolveProperties();

            std::string result = "";
            result += CompileVersion() + "\n";
            result += CompileLayouts() + "\n";
			result += CompileBody() + "\n";
            result += "void main(void){\n" + CompileSource() + "\n}\n";
            
            return result;
        }

        std::string Component::CompileVersion()
        {
            return "#version 430";
        }

        std::string Component::CompileLayouts()
        {
            std::string result = "";
            
            int count = 0;
            for (Property* property : uniforms)
                result += Util::formatted("layout(location = %i) uniform %s;\n", count++, property->DeclerationString());
            count = 0; result += "\n";
            for (Property* property : ins)
                result += Util::formatted("layout(location = %i) in %s;\n", count++, property->DeclerationString("in_"));
            count = 0; result += "\n";
            for (Property* property : outs)
                result += Util::formatted("layout(location = %i) out %s;\n", count++, property->DeclerationString("out_"));

            return result;
        }

		std::string Component::CompileBody()
		{
			std::string result = "";
			for (Snippet* snippet : snippets)
				result += snippet->body + "\n";
			return result;
		}

        std::string Component::CompileSource()
        {
            CreateConstantsSnippet();
            if (!ResolveSnippetOrder())
                return "";
            
            std::string result;
            for (Snippet* snippet : orderedSnippets)
                result += snippet->source + "\n";
            return result;
        }

        void Component::CreateConstantsSnippet()
        {
            std::string source = "";
            for (Property* property : constants)
                source += property->ValueString() + ";\n";
            constantsSnippet = new Snippet(source);
            constantsSnippet->propertiesOut.insert(constantsSnippet->propertiesOut.begin(), constants.begin(), constants.end());
        }

		void Component::ResolveProperties()
		{
			std::set<Property*> inputs;
			std::set<Property*> outputs;
		}

        bool Component::ResolveSnippetOrder()
        {
            std::set<Snippet*> currentSnippets(snippets);

            unsigned last_size = 0;
            while (currentSnippets.size() > 0)
            {
                if (snippets.size() == last_size)
                {
                    //Util::Log(LogType::Error, "Circular snippet dependencies detected when compiling %s shader; enable level logging 'info' to view snippet data", ComponentTypeName(type));
                    //for (Snippet* snippet : snippets)
                    //    Util::Log(LogType::Info, "\nSnippet Data:\n%s", snippet->source);
                    return false;
                }

                for (Snippet* snippet : currentSnippets)
                {
                    if (SnippetDependenciesMet(snippet))
                    {
                        orderedSnippets.push_back(snippet);
                        currentSnippets.erase(snippet);
                        for (Property* property : snippet->propertiesOut)
                            localProperties.insert(property);
                    }
                }
            }
        }

        bool Component::SnippetDependenciesMet(Snippet* snippet)
        {
            for (Property* property : snippet->propertiesIn)
                if (localProperties.find(property) == localProperties.end())
                    return false;
            return true;
        }
    }
}