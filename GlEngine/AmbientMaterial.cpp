#include "stdafx.h"
#include "AmbientMaterial.h"
#include "Shader.h"

#include "ShaderFactory.h"
#include "Property.h"
#include "Attribute.h"

#include "OpenGl.h"

namespace GlEngine
{
    AmbientMaterial::AmbientMaterial(Vector<3> color)
        : color(color)
    {
    }
    AmbientMaterial::~AmbientMaterial()
    {
    }

    void AmbientMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_RgbColor, color);
    }

    bool AmbientMaterial::IsOpaque()
    {
        return true;
    }

    TesselationType AmbientMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> AmbientMaterial::properties()
    {
        return{
            &ShaderFactory::prop_ModelMatrix,
            &ShaderFactory::prop_ViewMatrix,
            &ShaderFactory::prop_ProjectionMatrix,
            &ShaderFactory::prop_AmbientLightColor,
            &ShaderFactory::prop_RgbColor
        };
    }
    std::vector<ShaderFactory::Attribute*> AmbientMaterial::attributes()
    {
        return{
            &ShaderFactory::attr_GlPosition,
            &ShaderFactory::attr_AmbientLight
        };
    }

    const char *AmbientMaterial::name()
    {
        return "AmbientMaterial";
    }
    AmbientMaterial::operator bool()
    {
        return true;
    }
}
