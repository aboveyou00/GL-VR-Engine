#include "stdafx.h"
#include "FogSource.h"
#include "Property.h"
#include "ShaderFactory.h"

namespace GlEngine
{
    FogSource::FogSource(float mindist, float maxdist, Vector<4> color, FogInterpolationMode mode)
        : mindist(mindist), maxdist(maxdist), color(color), interpolationMode(mode)
    {
    }
    FogSource::~FogSource()
    {
    }

    void FogSource::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_FogMinDistance, mindist);
        factory.ProvideProperty(ShaderFactory::prop_FogMaxDistance, maxdist);
        factory.ProvideProperty(ShaderFactory::prop_FogColor, color);
    }
    std::vector<ShaderFactory::ShaderProp*> FogSource::properties()
    {
        return {
            &ShaderFactory::prop_FogMinDistance,
            &ShaderFactory::prop_FogMaxDistance,
            &ShaderFactory::prop_FogColor
        };
    }
}
