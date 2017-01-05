#pragma once

#include <set>
#include "Property.h"
#include "PropertySource.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Snippet : PropertySource 
        {
        public:
            Snippet(std::string mainSource, bool fallback = false, std::string declSource = ""s);
            Snippet(std::string mainSource, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> proportiesOut, bool fallback = false, std::string declSource = ""s);
            ~Snippet();

            std::string mainSource, declSource;
            std::vector<ShaderProp*> propertiesIn;
            std::vector<ShaderProp*> propertiesOut;

            bool fallback;

            static Snippet* IdentitySnippet(ShaderProp* prop)
            {
                return new Snippet("[OUT:0] = [IN:0]", {prop}, {prop});
            }

            virtual bool HasProperty(ShaderProp* prop) override;
            virtual void ProvideProperty(ShaderProp * prop, Program * program, ComponentType type) override;
        };
    }
}
