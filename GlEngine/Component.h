#pragma once

#include "ComponentType.h"
#include <set>

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ShaderProp;
        class Snippet;

        class ENGINE_SHARED Component
        {
        public:
            Component(ComponentType type);
            ~Component();

            ComponentType type;

            std::set<ShaderProp*> constants;
            std::set<ShaderProp*> uniforms;
            std::set<ShaderProp*> ins;
            std::set<ShaderProp*> outs;

            std::set<Snippet*> snippets;

            unsigned FindOrCreateOutput(ShaderProp* prop);
            virtual std::string Compile();

        private:
            std::string CompileVersion();
            std::string CompileLayouts();
            std::string CompileBody();
            std::string CompileSource();

            std::set<ShaderProp*> localProperties;
            std::vector<Snippet*> orderedSnippets;
            //bool ResolveSnippetOrder();
            //bool SnippetDependenciesMet(Snippet* snippet);
        };
    }
}
