#include "stdafx.h"
#include "ClipPlaneMaterial.h"
#include "Texture.h"
#include "Attribute.h"
#include "Property.h"
#include "ShaderFactory.h"

namespace GlEngine
{
    ClipPlaneMaterial::ClipPlaneMaterial(std::string name, Vector<4> color)
        : Material(name, true), tex(nullptr), color(color)
    {
    }
    ClipPlaneMaterial::ClipPlaneMaterial(std::string name, Texture *tex)
        : Material(name, true), tex(tex)
    {
    }
    ClipPlaneMaterial::~ClipPlaneMaterial()
    {
    }

    void ClipPlaneMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        if (tex != nullptr) factory.ProvideProperty(ShaderFactory::prop_Texture, tex);
        else factory.ProvideProperty(ShaderFactory::prop_BaseColor, color);
        factory.ProvideProperty(ShaderFactory::prop_LightColor, { 1.f, 1.f, 1.f });
    }

    std::vector<ShaderFactory::Attribute*> ClipPlaneMaterial::attributes()
    {
        std::vector<ShaderFactory::Attribute*> attrs = {};
        if (tex != nullptr) attrs.push_back(&ShaderFactory::attr_TextureBaseColor);
        attrs.push_back(&ShaderFactory::attr_GlClipPosition);
        return attrs;
    }
    std::vector<ShaderFactory::ShaderProp*> ClipPlaneMaterial::properties()
    {
        std::vector<ShaderFactory::ShaderProp*> props = {};
        if (tex != nullptr) props.push_back(&ShaderFactory::prop_Texture);
        props.push_back(&ShaderFactory::prop_BaseColor);
        props.push_back(&ShaderFactory::prop_LightColor);
        return props;
    }

    bool ClipPlaneMaterial::IsOpaque()
    {
        return tex == nullptr ? color[3] == 1 : tex->IsOpaque();
    }
    TesselationType ClipPlaneMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    bool ClipPlaneMaterial::isReady()
    {
        return tex == nullptr || tex->isReady();
    }
}
