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

            void AddComment(std::string comment, int tabulation = 4);

        private:
            void compileVersion(std::stringstream &stream);
            void compileLayouts(std::stringstream &stream);
            void compileDecl(std::stringstream &stream);
            void compilePropertyDeclarations(std::stringstream &stream, int tabulation = 4);
            void compileMain(std::stringstream &stream, int tabulation = 4);

            bool snippetDependenciesMet(Snippet* snippet);

            void addLocalProp(ShaderProp *prop);
        };
    }
}
