#include "stdafx.h"
#include "AmbientMaterial.h"
#include "Shader.h"

#include "ShaderFactory.h"
#include "Property.h"
#include "Attribute.h"

#include "Texture.h"
#include "OpenGl.h"

namespace GlEngine
{
    AmbientMaterial::AmbientMaterial(Vector<3> color)
        : color(color)
    {
    }
    AmbientMaterial::AmbientMaterial(Texture *texture)
        : texture(texture)
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
        if (texture == nullptr) return true;
        else return texture->IsOpaque();
    }

    TesselationType AmbientMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> AmbientMaterial::properties()
    {
        std::vector<ShaderFactory::ShaderProp*> props = { };
        if (texture == nullptr) props.push_back(&ShaderFactory::prop_RgbColor);
        else props.push_back(&ShaderFactory::prop_Texture);
        return props;
    }
    std::vector<ShaderFactory::Attribute*> AmbientMaterial::attributes()
    {
        std::vector<ShaderFactory::Attribute*> attrs = { };
        if (texture == nullptr) attrs.push_back(&ShaderFactory::attr_RgbBaseColor);
        else attrs.push_back(&ShaderFactory::attr_TextureBaseColor);
        attrs.push_back(&ShaderFactory::attr_GlPosition);
        attrs.push_back(&ShaderFactory::attr_AmbientOnly);
        return attrs;
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
