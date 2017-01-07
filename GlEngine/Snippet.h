#pragma once

#include <set>
#include "Property.h"
#include "PropertySource.h"
#include "SnippetFlag.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Snippet : PropertySource 
        {
        public:
            Snippet(std::string mainSource, SnippetFlag flags = SnippetFlag::None, std::string declSource = ""s);
            Snippet(std::string mainSource, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> proportiesOut, SnippetFlag flags = SnippetFlag::None, std::string declSource = ""s);
            ~Snippet();

            Snippet* Copy();

            std::string mainSource, declSource;
            std::vector<ShaderProp*> propertiesIn;
            std::vector<ShaderProp*> propertiesOut;

            static Snippet* IdentitySnippet(ShaderProp* prop, bool input, bool output);
            virtual bool HasProperty(ShaderProp* prop) override;
            virtual void ProvideProperty(ShaderProp * prop, Program * program, ComponentType type) override;

            bool HasFlag(SnippetFlag flag) const;
            void SetFlag(SnippetFlag flag, bool val);
            void SetFlag(SnippetFlag flag);
            void ResetFlag(SnippetFlag flag);

            bool fallback() const;
            bool noSideEffects() const;
            bool hasSideEffects() const;

        private:
            SnippetFlag flags;
        };
    }
}
