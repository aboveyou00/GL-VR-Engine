#pragma once

#include "ComponentType.h"
#include <set>

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Property;
        class Snippet;

        //class ENGINE_SHARED Component
        //{
        //public:
        //    Component(ComponentType type);
        //    ~Component();

        //    ComponentType type;

<<<<<<< HEAD
            std::set<Property*> constants;
            std::set<Property*> uniforms;
            std::set<Property*> ins;
            std::set<Property*> outs;
=======
        //    std::vector<Property*> constants;
        //    std::vector<Property*> uniforms;
        //    std::vector<Property*> ins;
        //    std::vector<Property*> outs;
>>>>>>> 9a332fad24e8f2e4cf0df4e95d7ead07270d041e

        //    std::set<Snippet*> snippets;

        //    virtual std::string Compile();

<<<<<<< HEAD
        private:
            std::string CompileVersion();
            std::string CompileLayouts();
			std::string CompileBody();
            std::string CompileSource();
=======
        //private:
        //    std::string CompileVersion();
        //    std::string CompileLayouts();
        //    std::string CompileBody();
>>>>>>> 9a332fad24e8f2e4cf0df4e95d7ead07270d041e

        //    Snippet* constantsSnippet;
        //    void CreateConstantsSnippet();

<<<<<<< HEAD
			void ResolveProperties();
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
=======
        //    std::set<Property*> localProperties;
        //    std::vector<Snippet*> orderedSnippets;
        //    bool ResolveSnippetOrder();
        //    bool SnippetDependenciesMet(Snippet* snippet);
        //};
>>>>>>> 9a332fad24e8f2e4cf0df4e95d7ead07270d041e
    }
}
