#include "stdafx.h"
#include "DummyPropertySource.h"
#include "ShaderProp.h"

namespace GlEngine::ShaderFactory
{
    DummyPropertySource &DummyPropertySource::instance()
    {
        static DummyPropertySource inst;
        return inst;
    }
    
    DummyPropertySource::DummyPropertySource()
    {
    }
    DummyPropertySource::~DummyPropertySource()
    {
    }

    bool DummyPropertySource::HasProperty(ShaderProp *prop)
    {
        return prop->hasFlag(PropertyFlag::Resolved);
    }
    void DummyPropertySource::Inject(Program*, ComponentType)
    {
    }
    const std::vector<ShaderProp*> DummyPropertySource::outProperties()
    {
        assert(false);
        return { };
    }

    void DummyPropertySource::ProvideInput(Program*, ShaderProp*, ComponentType, ComponentType)
    {
    }
}
