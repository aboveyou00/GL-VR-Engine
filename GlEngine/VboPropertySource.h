#pragma once

#include "Property.h"
#include "PropertySource.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED VboPropertySource : public PropertySource
        {
        public:
            template <typename... TArgs>
            VboPropertySource(Property<TArgs>*... properties)
            {
                static_assert(sizeof...(TArgs) >= 1, "VboPropertySource must be created with at least one property");
                ctor(properties...);
            }
            VboPropertySource(std::vector<ShaderProp*> properties, PropertySourceFlag flags = PropertySourceFlag::None);
            ~VboPropertySource();

            virtual bool HasProperty(ShaderProp * prop) override;
            virtual const std::vector<ShaderProp*> outProperties() override;
            virtual void Inject(Program * program, ComponentType type) override;

        private:
            template <typename T, typename... TArgs>
            inline void ctor(Property<T> *t, Property<TArgs>*... otherArgs)
            {
                ctor(t);
                ctor(otherArgs...);
            }
            template <typename T>
            inline void ctor(Property<T> *t)
            {
                assert(t != nullptr);
                _props.push_back(t);
            }
            
            std::vector<ShaderProp*> _props;
        };
    }
}
