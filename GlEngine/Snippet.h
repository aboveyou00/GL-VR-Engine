#pragma once

#include <set>
#include "Property.h"
#include "PropertySource.h"
#include "SnippetFlag.h"
#include "StringUtils.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Snippet : PropertySource 
        {
        public:
            Snippet(std::string mainSource, SnippetFlag flags = SnippetFlag::None, std::string declSource = ""s);
            Snippet(std::string mainSource, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> propertiesOut, SnippetFlag flags = SnippetFlag::None, std::string declSource = ""s);
            ~Snippet();

            template <typename... TArgs>
            Snippet *WithTemps()
            {
                static_assert(sizeof...(TArgs) > 0, "You must pass at least one property type to WithTemps");
                this->createTemps<0, TArgs...>();
                return this;
            }

            Snippet* Copy();

            std::string mainSource, declSource;
            std::vector<ShaderProp*> propertiesIn, propertiesOut, tempProperties;

            static Snippet* IdentitySnippet(ShaderProp* prop, bool input, bool output);
            virtual bool HasProperty(ShaderProp* prop) override;
            virtual void ProvideProperty(ShaderProp * prop, Program * program, ComponentType type) override;

            bool hasFlag(SnippetFlag flag) const;
            void SetFlag(SnippetFlag flag, bool val);
            void SetFlag(SnippetFlag flag);
            void ResetFlag(SnippetFlag flag);

            bool fallback() const;
            bool noSideEffects() const;
            bool hasSideEffects() const;

        private:
            template <unsigned idx = 0, typename T, typename... TArgs>
            inline void createTemps()
            {
                std::stringstream stream;
                stream << "temp_"s << Util::addressString(this) << "_"s << idx;
                auto tempProp = new Property<T>(stream.str());
                tempProperties.push_back(tempProp);
                createTemps<idx + 1, TArgs...>();
            }
            template <unsigned idx = 0>
            inline void createTemps()
            {
            }

            SnippetFlag flags;
        };
    }
}
