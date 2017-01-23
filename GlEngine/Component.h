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

            unsigned FindOrCreateOutput(ShaderProp* prop);
            virtual std::string Compile();
            std::string compiled;

			void AddIdentitySnippet(ShaderProp* prop, bool input, bool output);
			void AddSnippet(Snippet* snippet);
            void AddUnresolvedSnippet(Snippet* snippet, int tabulation = 4);
			std::set<ShaderProp*> allProps;

        private:
            std::vector<Snippet*> snippets;
			std::vector<Snippet*> inputSnippets;
			std::vector<Snippet*> outputSnippets;

            std::string comments;

            void compileVersion(std::stringstream &stream);
            void compileLayouts(std::stringstream &stream);
            void compileDecl(std::stringstream &stream);
            void compilePropertyDeclarations(std::stringstream &stream, int tabulation = 4);
            void compileMain(std::stringstream &stream, int tabulation = 4);
        };
    }
}
