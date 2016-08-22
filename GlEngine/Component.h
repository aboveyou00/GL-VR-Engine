#pragma once

#include "Property.h"
#include "Snippet.h"
#include <set>
#include <numeric>

namespace GlEngine
{
	namespace ShaderFactory
	{
		enum class ENGINE_SHARED ComponentType
		{
			Vertex = 0,
			TessControl = 1,
			TessEvaluation = 2,
			Geometry = 3,
			Fragment = 4
		};
		extern std::string ComponentTypeName(ComponentType type)
		{
			switch (type)
			{
			case ComponentType::Vertex:
				return "Vertex";
			case ComponentType::TessControl:
				return "TessControl";
			case ComponentType::TessEvaluation:
				return "TessEvaluation";
			case ComponentType::Geometry:
				return "Geometry";
			case ComponentType::Fragment:
				return "Fragment";
			}
			return "";
		}

		class ENGINE_SHARED Component
		{
		public:
			Component(ComponentType type);
			~Component();

			ComponentType type;

			std::vector<Property*> constants;
			std::vector<Property*> uniforms;
			std::vector<Property*> ins;
			std::vector<Property*> outs;

			std::set<Snippet*> snippets;

			std::string Compile();

		private:
			std::string CompileVersion();
			std::string CompileLayouts();
			std::string CompileBody();

			std::set<Property*> localProperties;
			std::vector<Snippet*> orderedSnippets;
			bool ResolveSnippetOrder();
			bool SnippetDependenciesMet(Snippet* snippet);
		};

		class ENGINE_SHARED ComponentArray
		{
		public:
			ComponentArray(int length);
			~ComponentArray();

			Component*& operator[](int index);
			Component*& operator[](ComponentType index);

		private:
			Component** _components;
		};
	}
}

GlEngine::ShaderFactory::ComponentType std::numeric_limits<GlEngine::ShaderFactory::ComponentType>::min()
{
	return GlEngine::ShaderFactory::ComponentType::Vertex;
}
GlEngine::ShaderFactory::ComponentType std::numeric_limits<GlEngine::ShaderFactory::ComponentType>::max()
{
	return GlEngine::ShaderFactory::ComponentType::Fragment;
}