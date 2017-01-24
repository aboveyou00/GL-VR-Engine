#include "stdafx.h"
#include "SpotlightSource.h"
#include "Property.h"
#include "ShaderFactory.h"

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
        return {
            &ShaderFactory::prop_PointLightPosition,
            &ShaderFactory::prop_DiffuseLightColor,
            &ShaderFactory::prop_SpecularLightColor,

            &ShaderFactory::prop_SpotlightPosition,
            &ShaderFactory::prop_SpotlightColor,
            &ShaderFactory::prop_SpotlightDirection,
            &ShaderFactory::prop_SpotlightAttenuation,
            &ShaderFactory::prop_SpotlightCutoffAngle
        };
    }

    void SpotlightSource::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_PointLightPosition, _position);
        factory.ProvideProperty(ShaderFactory::prop_DiffuseLightColor, _color);
        factory.ProvideProperty(ShaderFactory::prop_SpecularLightColor, _color);

        factory.ProvideProperty(ShaderFactory::prop_SpotlightPosition, _position);
        factory.ProvideProperty(ShaderFactory::prop_SpotlightColor, _color);
        factory.ProvideProperty(ShaderFactory::prop_SpotlightDirection, _direction);
        factory.ProvideProperty(ShaderFactory::prop_SpotlightAttenuation, _angleAttenuation);
        factory.ProvideProperty(ShaderFactory::prop_SpotlightCutoffAngle, _cutoffTheta);
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
