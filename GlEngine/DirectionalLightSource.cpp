#include "stdafx.h"
#include "DirectionalLightSource.h"

namespace GlEngine
{
    DirectionalLightSource::DirectionalLightSource(Vector<3> direction, Vector<3> color)
        : _direction(direction), _color(color)
    {
    }
    DirectionalLightSource::~DirectionalLightSource()
    {
    }

    std::vector<ShaderFactory::ShaderProp*> DirectionalLightSource::properties()
    {
        return { };
    }

    void DirectionalLightSource::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory;
        assert(false);
    }

    Vector<3> DirectionalLightSource::direction()
    {
        return _direction;
    }
    void DirectionalLightSource::SetDirection(Vector<3> direction)
    {
        _direction = direction;
    }

    Vector<3> DirectionalLightSource::color()
    {
        return _color;
    }
    void DirectionalLightSource::SetColor(Vector<3> color)
    {
        _color = color;
    }
}
