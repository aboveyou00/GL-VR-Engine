#include "stdafx.h"
#include "PointLightSource.h"
#include "ShaderFactory.h"
#include "Property.h"

namespace GlEngine
{
    PointLightSource::PointLightSource(Vector<3> pos, Vector<3> diffuseColor, Vector<3> specularColor, bool attenuation)
        : _pos(pos), _diffuseColor(diffuseColor), _specularColor(specularColor), _attenuation(attenuation)
    {
    }
    PointLightSource::~PointLightSource()
    {
    }

    void PointLightSource::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_PointLightPosition, _pos);
        factory.ProvideProperty(ShaderFactory::prop_DiffuseLightColor, _diffuseColor);
        factory.ProvideProperty(ShaderFactory::prop_SpecularLightColor, _specularColor);
        factory.ProvideStructProperty(ShaderFactory::prop_PointLightInfo, _pos, _diffuseColor, _attenuation);
    }

    std::vector<ShaderFactory::ShaderProp*> PointLightSource::properties()
    {
        return {
            &ShaderFactory::prop_PointLightPosition,
            &ShaderFactory::prop_DiffuseLightColor,
            &ShaderFactory::prop_SpecularLightColor,
            &ShaderFactory::prop_PointLightInfo
        };
    }

    Vector<3> PointLightSource::position()
    {
        return _pos;
    }
    void PointLightSource::SetPosition(Vector<3> pos)
    {
        this->_pos = pos;
    }

    Vector<3> PointLightSource::diffuseColor()
    {
        return _diffuseColor;
    }
    void PointLightSource::SetDiffuseColor(Vector<3> color)
    {
        this->_diffuseColor = color;
    }
    
    Vector<3> PointLightSource::specularColor()
    {
        return _specularColor;
    }
    void PointLightSource::SetSpecularColor(Vector<3> color)
    {
        this->_specularColor = color;
    }

    bool PointLightSource::attenuation()
    {
        return _attenuation;
    }
    void PointLightSource::SetAttenuation(bool val)
    {
        _attenuation = val;
    }
}
