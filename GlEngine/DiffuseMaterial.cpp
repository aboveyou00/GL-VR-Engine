#include "stdafx.h"
#include "DiffuseMaterial.h"
#include "Shader.h"

#include "ShaderFactory.h"
#include "Property.h"
#include "Attribute.h"

#include "OpenGl.h"

namespace GlEngine
{
    DiffuseMaterial::DiffuseMaterial(Vector<3> color, Vector<3> reflectionCoef)
        : color(color), reflectionCoef(reflectionCoef)
    {
    }
    DiffuseMaterial::~DiffuseMaterial()
    {
    }

    void DiffuseMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_RgbColor, color);
        factory.ProvideProperty(ShaderFactory::prop_ReflectionCoefficient, reflectionCoef);
    }

    bool DiffuseMaterial::IsOpaque()
    {
        return true;
    }

    TesselationType DiffuseMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> DiffuseMaterial::properties()
    {
        return {
            &ShaderFactory::prop_ModelMatrix,
            &ShaderFactory::prop_ViewMatrix,
            &ShaderFactory::prop_ProjectionMatrix,
            &ShaderFactory::prop_DiffuseLightPosition,
            &ShaderFactory::prop_DiffuseLightColor,
            &ShaderFactory::prop_RgbColor,
            &ShaderFactory::prop_ReflectionCoefficient
        };
    }
    std::vector<ShaderFactory::Attribute*> DiffuseMaterial::attributes()
    {
        return {
            &ShaderFactory::attr_GlPosition,
            &ShaderFactory::attr_DiffuseLight
        };
    }

    const char *DiffuseMaterial::name()
    {
        return "DiffuseMaterial";
    }
    DiffuseMaterial::operator bool()
    {
        return true;
    }
}
