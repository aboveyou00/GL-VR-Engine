#pragma once

#include "PropertySource.h"
#include "Program.h"
#include "Property.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        template<typename T>
        class ConstantPropertySource : PropertySource
        {
        public:
            ConstantPropertySource(Property<T> prop, T value)
                : prop(prop), value(value)
            {
            }

            virtual bool HasProperty(ShaderProp * prop) override
            {
                return this->prop == prop;
            }
            virtual void ProvideProperty(ShaderProp * prop, Program * program, ComponentType type) override
            {
            }
            virtual std::string PropertyName(ShaderProp * prop)
            {
                if (HasProperty())
                    return Property<T>::ValueString(value);
                return "[ERROR]";
            }

        private:
            Property<T> prop;
            T value;
        };
    }
}
