#pragma once

#include <set>
#include "Property.h"
#include "PropertySource.h"
#include "StringUtils.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Snippet : public PropertySource 
        {
        public:
            Snippet(std::string mainSource, PropertySourceFlag flags = PropertySourceFlag::None, std::vector<ComponentType> supportedComponents = { ComponentType::Vertex, ComponentType::Fragment }, std::string declSource = ""s);
            Snippet(std::string mainSource, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> propertiesOut, PropertySourceFlag flags = PropertySourceFlag::None, std::vector<ComponentType> supportedComponents = { ComponentType::Vertex, ComponentType::Fragment }, std::string declSource = ""s);
            ~Snippet();

            template <typename... TArgs>
            Snippet *WithTemps()
            {
                static_assert(sizeof...(TArgs) > 0, "You must pass at least one property type to WithTemps");
                this->createTemps<0, TArgs...>();
                return this;
            }

            std::string mainSource, declSource;
            std::vector<ShaderProp*> propertiesIn, propertiesOut, tempProperties;

            static Snippet* IdentitySnippet(ShaderProp* prop, bool input, bool output);
            virtual bool HasProperty(ShaderProp* prop) override;
            virtual const std::vector<ShaderProp*> inProperties() override;
            virtual const std::vector<ShaderProp*> outProperties() override;
            virtual void ProvideProperty(ShaderProp * prop, Program * program, ComponentType type) override;

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
        };
    }
}
