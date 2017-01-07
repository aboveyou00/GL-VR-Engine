#pragma once

#include "VBOFactory.h"
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
            VboPropertySource(std::vector<ShaderProp*> properties)
            {
                assert(properties.size() >= 1);
                for (size_t q = 0; q < properties.size(); q++)
                {
                    assert(properties[q] != nullptr);
                    _props.push_back(properties[q]);
                }
            }

            virtual bool HasProperty(ShaderProp * prop) override;
            virtual void ProvideProperty(ShaderProp * prop, Program * program, ComponentType type) override;

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
