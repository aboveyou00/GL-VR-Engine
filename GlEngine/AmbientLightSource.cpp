#include "stdafx.h"
#include "AmbientLightSource.h"
#include "ShaderFactory.h"
#include "Property.h"

namespace GlEngine
{
    AmbientLightSource::AmbientLightSource(Vector<3> color)
        : _color(color)
    {
    }
    AmbientLightSource::~AmbientLightSource()
    {
    }

    std::vector<ShaderFactory::ShaderProp*> AmbientLightSource::properties()
    {
        return {
            &ShaderFactory::prop_AmbientLightColor
        };
    }
    
    void AmbientLightSource::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_AmbientLightColor, _color);
    }

    Vector<3> AmbientLightSource::color()
    {
        return _color;
    }
    void AmbientLightSource::SetColor(Vector<3> color)
    {
        _color = color;
    }
}
