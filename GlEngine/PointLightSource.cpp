#include "stdafx.h"
#include "PointLightSource.h"
#include "ShaderFactory.h"
#include "Property.h"

namespace GlEngine
{
    PointLightSource::PointLightSource(Vector<3> pos, Vector<3> diffuseColor, Vector<3> specularColor)
        : _pos(pos), _diffuseColor(diffuseColor), _specularColor(specularColor)
    {
    }
    PointLightSource::~PointLightSource()
    {
    }
    
    std::vector<ShaderFactory::ShaderProp*> PointLightSource::properties()
    {
        return {
            &ShaderFactory::prop_PointLightPosition,
            &ShaderFactory::prop_DiffuseLightColor,
            &ShaderFactory::prop_SpecularLightColor
        };
    }

    void PointLightSource::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_PointLightPosition, _pos);
        factory.ProvideProperty(ShaderFactory::prop_DiffuseLightColor, _diffuseColor);
        factory.ProvideProperty(ShaderFactory::prop_SpecularLightColor, _specularColor);
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
}
