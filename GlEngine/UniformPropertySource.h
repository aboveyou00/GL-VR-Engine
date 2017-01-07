#pragma once

#include "PropertySource.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED UniformPropertySource : public PropertySource
        {
        public:
            UniformPropertySource(ShaderProp* prop);

            virtual bool HasProperty(ShaderProp * prop) override;
            virtual void ProvideProperty(ShaderProp * prop, Program * program, ComponentType type) override;

        private:
            ShaderProp* prop;
        };
    }
}