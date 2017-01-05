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

        //    std::vector<Property*> constants;
        //    std::vector<Property*> uniforms;
        //    std::vector<Property*> ins;
        //    std::vector<Property*> outs;

        //    std::set<Snippet*> snippets;

        //    virtual std::string Compile();

        //private:
        //    std::string CompileVersion();
        //    std::string CompileLayouts();
        //    std::string CompileBody();

        //    Snippet* constantsSnippet;
        //    void CreateConstantsSnippet();

        //    std::set<Property*> localProperties;
        //    std::vector<Snippet*> orderedSnippets;
        //    bool ResolveSnippetOrder();
        //    bool SnippetDependenciesMet(Snippet* snippet);
        //};
    }
}
