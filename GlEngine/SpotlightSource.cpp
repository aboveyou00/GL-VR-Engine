#include "stdafx.h"
#include "SpotlightSource.h"

namespace GlEngine
{
    SpotlightSource::SpotlightSource(Vector<3> position, Vector<3> color, float angleAttenuation, Vector<3> direction, float cutoffTheta)
        : _position(position), _color(color), _angleAttenuation(angleAttenuation), _direction(direction), _cutoffTheta(cutoffTheta)
    {
    }
    SpotlightSource::~SpotlightSource()
    {
    }

    std::vector<ShaderFactory::ShaderProp*> SpotlightSource::properties()
    {
        return { };
    }

    void SpotlightSource::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory;
        assert(false);
    }

    void SpotlightSource::SetPosition(Vector<3> position)
    {
        _position = position;
    }
    Vector<3> SpotlightSource::position()
    {
        return _position;
    }

    void SpotlightSource::SetColor(Vector<3> color)
    {
        _color = color;
    }
    Vector<3> SpotlightSource::color()
    {
        return _color;
    }

    void SpotlightSource::SetDirection(Vector<3> direction)
    {
        _direction = direction;
    }
    Vector<3> SpotlightSource::direction()
    {
        return _direction;
    }

    void SpotlightSource::SetAngleAttenuation(float attenuation)
    {
        _angleAttenuation = attenuation;
    }
    float SpotlightSource::angleAttenuation()
    {
        return _angleAttenuation;
    }

    void SpotlightSource::SetCutoffTheta(float cutoffTheta)
    {
        _cutoffTheta = cutoffTheta;
    }
    float SpotlightSource::cutoffTheta()
    {
        return _cutoffTheta;
    }
}
