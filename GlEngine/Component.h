#pragma once

#include "ComponentType.h"
#include <set>
#include <map>

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

            std::map<unsigned, ShaderProp*> ins, outs, uniforms;
            std::set<ShaderProp*> unresolvedInputs, availableLocalProps, unresolvedOutputs;
            std::set<Snippet*> unresolvedSnippets;
            std::vector<Snippet*> orderedSnippets;

            bool ResolveSnippets();
            bool IsResolved();

            unsigned FindOrCreateOutput(ShaderProp* prop);
            virtual std::string Compile();
            std::string compiled;

        private:
            std::string compileVersion();
            std::string compileLayouts();
            std::string compileDecl();
            std::string compileMain();

            bool snippetDependenciesMet(Snippet* snippet);

            void addLocalProp(ShaderProp *prop);
        };
    }
}
