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

            std::vector<ShaderProp*> ins, outs;
            std::set<ShaderProp*> unresolvedInputs, availableLocalProps, unresolvedOutputs;

            std::set<Snippet*> unresolvedSnippets;

            unsigned FindOrCreateOutput(ShaderProp* prop);

            bool ResolveSnippets();
            bool IsResolved();

            virtual std::string Compile();

        private:
            std::string compileVersion();
            std::string compileLayouts();
            std::string compileBody();
            std::string compileSource();

            std::vector<Snippet*> orderedSnippets;
            bool snippetDependenciesMet(Snippet* snippet);

            void addLocalProp(ShaderProp *prop);
        };
    }
}
