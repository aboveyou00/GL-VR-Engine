#include "stdafx.h"
#include "Image2dMaterial.h"
#include "Texture.h"
#include "Shader.h"

#include "Property.h"
#include "Attribute.h"
#include "ShaderFactory.h"

namespace GlEngine
{
    Image2dMaterial::Image2dMaterial()
        : Material(true)
    {
    }
    Image2dMaterial::~Image2dMaterial()
    {
    }

    void Image2dMaterial::SetTexture(Texture *tex)
    {
        this->tex = tex;
    }

    void Image2dMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_Texture, tex);
    }

    bool Image2dMaterial::IsOpaque()
    {
        return !tex || tex->IsOpaque();
    }
    TesselationType Image2dMaterial::GetTesselationType()
    {
        return GlEngine::TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> Image2dMaterial::properties()
    {
        return {
            &GlEngine::ShaderFactory::prop_Texture
        };
    }
    std::vector<ShaderFactory::Attribute*> Image2dMaterial::attributes()
    {
        return {
            &GlEngine::ShaderFactory::attr_Image2d
        };
    }

    const char *Image2dMaterial::name()
    {
        return "Image2dMaterial";
    }
    Image2dMaterial::operator bool()
    {
        return tex && *tex;
    }
}
