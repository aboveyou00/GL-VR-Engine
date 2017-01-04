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

            virtual std::string Compile();

        private:
            std::string CompileVersion();
            std::string CompileLayouts();
            std::string CompileBody();

            Snippet* constantsSnippet;
            void CreateConstantsSnippet();

            std::set<Property*> localProperties;
            std::vector<Snippet*> orderedSnippets;
            bool ResolveSnippetOrder();
            bool SnippetDependenciesMet(Snippet* snippet);
        };

        //TODO iterator
        template<typename T>
        class ComponentArray
        {
        public:
            ComponentArray(unsigned length)
            {
                _components = new T[length];
                size = length;
            }
            ComponentArray(std::vector<T> data)
            {
                _components = new T[data.size()];
                size = data.size();
                for (unsigned i = 0; i < data.size(); i++)
                    _components[i] = data[i];
            }
            ~ComponentArray()
            {
                delete[] _components;
            }

            T& operator[](int index)
            {
                return _components[index];
            }
            T& operator[](ComponentType index)
            {
                return _components[(unsigned)index];
            }
            size_t size()
            {
                return size;
            }

        private:
            size_t size;
            T* _components;
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