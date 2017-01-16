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
            std::vector<Snippet*> snippets;

            unsigned FindOrCreateOutput(ShaderProp* prop);
            virtual std::string Compile();
            std::string compiled;

            void AddUnresolvedSnippet(Snippet* snippet, int tabulation = 4);

        private:
            std::string comments;

            void compileVersion(std::stringstream &stream);
            void compileLayouts(std::stringstream &stream);
            void compileDecl(std::stringstream &stream);
            void compilePropertyDeclarations(std::stringstream &stream, int tabulation = 4);
            void compileMain(std::stringstream &stream, int tabulation = 4);
        };
    }
}
