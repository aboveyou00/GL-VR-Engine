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
		}

		std::string Component::Compile()
		{
			std::string result = "";
			result += CompileVersion() + "\n";
			result += CompileLayouts() + "\n";
			// TOOD: subroutines
			result += "void main(void){\n" + CompileBody() + "\n}\n";
			
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
			if (!ResolveSnippetOrder())
				return "";
			
			std::string result;
			for (Snippet* snippet : orderedSnippets)
				result += snippet->source + "\n";
			return result;
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
					//	Util::Log(LogType::Info, "\nSnippet Data:\n%s", snippet->source);
					return false;
				}

				for (Snippet* snippet : currentSnippets)
				{
					if (SnippetDependenciesMet(snippet))
					{
						orderedSnippets.push_back(snippet);
						currentSnippets.erase(snippet);
						for (Property* property : snippet->LocalPropertiesOut)
							localProperties.insert(property);
					}
				}
			}
		}

		bool Component::SnippetDependenciesMet(Snippet* snippet)
		{
			for (Property* property : snippet->LocalPropertiesIn)
				if (localProperties.find(property) == localProperties.end())
					return false;
			return true;
		}
	
		ComponentArray::ComponentArray(int size)
		{
			_components = new Component*[size];
		}
		ComponentArray::~ComponentArray()
		{
			delete[] _components;
		}
		Component*& ComponentArray::operator[](int index)
		{
			return _components[index];
		}
		Component*& ComponentArray::operator[](ComponentType index)
		{
			return _components[(unsigned)index];
		}
	}
}