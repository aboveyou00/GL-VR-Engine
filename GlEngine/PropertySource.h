#pragma once

#include "ComponentType.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ShaderProp;
        class Program;

        class ENGINE_SHARED PropertySource
        {
        public:
            PropertySource();
            ~PropertySource();

            virtual bool HasProperty(ShaderProp* prop) = 0;
            virtual void ProvideProperty(ShaderProp* prop, Program* program, ComponentType type) = 0;
            virtual std::string PropertyName(ShaderProp* prop);
        };
    }
}
