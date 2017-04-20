#include "stdafx.h"
#include "ClipPlaneMaterial.h"
#include "Texture.h"
#include "Attribute.h"
#include "Property.h"
#include "ShaderFactory.h"

ClipPlaneMaterial::ClipPlaneMaterial(std::string name, Vector<4> color)
    : GlEngine::Material(name, true), tex(nullptr), color(color)
{
}
ClipPlaneMaterial::ClipPlaneMaterial(std::string name, GlEngine::Texture *tex)
    : GlEngine::Material(name, true), tex(tex)
{
}
ClipPlaneMaterial::~ClipPlaneMaterial()
{
}

void ClipPlaneMaterial::Push(GlEngine::ShaderFactory::ShaderFactory &factory)
{
    if (tex != nullptr) factory.ProvideProperty(GlEngine::ShaderFactory::prop_Texture, tex);
    else factory.ProvideProperty(GlEngine::ShaderFactory::prop_BaseColor, color);
    factory.ProvideProperty(GlEngine::ShaderFactory::prop_LightColor, { 1.f, 1.f, 1.f });
}

std::vector<GlEngine::ShaderFactory::Attribute*> ClipPlaneMaterial::attributes()
{
    std::vector<GlEngine::ShaderFactory::Attribute*> attrs = {};
    if (tex != nullptr) attrs.push_back(&GlEngine::ShaderFactory::attr_TextureBaseColor);
    attrs.push_back(&GlEngine::ShaderFactory::attr_GlClipPosition);
    return attrs;
}
std::vector<GlEngine::ShaderFactory::ShaderProp*> ClipPlaneMaterial::properties()
{
    std::vector<GlEngine::ShaderFactory::ShaderProp*> props = {};
    if (tex != nullptr) props.push_back(&GlEngine::ShaderFactory::prop_Texture);
    props.push_back(&GlEngine::ShaderFactory::prop_BaseColor);
    props.push_back(&GlEngine::ShaderFactory::prop_LightColor);
    return props;
}

bool ClipPlaneMaterial::IsOpaque()
{
    return tex == nullptr ? color[3] == 1 : tex->IsOpaque();
}
GlEngine::TesselationType ClipPlaneMaterial::GetTesselationType()
{
    return GlEngine::TesselationType::Disabled;
}

bool ClipPlaneMaterial::isReady()
{
    return tex == nullptr || tex->isReady();
}
