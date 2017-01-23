#pragma once

#include "PropertySource.h"

namespace GlEngine::ShaderFactory
{
    class DummyPropertySource : public PropertySource
    {
    public:
        static DummyPropertySource &instance();

    private:
        DummyPropertySource();
        ~DummyPropertySource();

    public:
        virtual bool HasProperty(ShaderProp *prop) override;
        virtual void Inject(Program *program, ComponentType type) override;
        virtual const std::vector<ShaderProp*> outProperties() override;
        virtual void ProvideInput(Program* program, ShaderProp* prop, ComponentType inputType, ComponentType sourceType) override;
    };
}
