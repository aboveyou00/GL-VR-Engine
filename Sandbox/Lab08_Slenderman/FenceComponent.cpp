#include "stdafx.h"
#include "FenceComponent.h"
#include "GameObject.h"
#include "ObjGraphicsObject.h"
#include "Texture.h"
#include "Attribute.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "RandomUtils.h"
#include "MathUtils.h"

extern Attribute attr_PhongFog;

FenceComponent::FenceComponent()
    : GlEngine::GameComponent("Fence")
{
}
FenceComponent::~FenceComponent()
{
}

GlEngine::GameObject *FenceComponent::Create(GlEngine::Frame *frame, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers)
{
    auto pageGobj = new GlEngine::GameObject(frame, "Page");
    auto pageComp = new FenceComponent();
    pageGobj->AddComponent(pageComp);
    pageGobj->localTransform()->Scale({ 2, 2, 2 });

    auto fenceGfx = new GlEngine::ObjGraphicsObject("FenceGfx", "Resources/fence.obj");
    auto fenceTex = GlEngine::Texture::FromFile("Textures/fence.png"s, GlEngine::TextureFlag::Translucent);
    auto fenceMaterial = TemplateMaterial::Factory()
        ->Attribute(&GlEngine::ShaderFactory::attr_GlPosition)
        ->Attribute(&GlEngine::ShaderFactory::attr_Phong)
        ->Attribute(&GlEngine::ShaderFactory::attr_TextureBaseColor)
        ->Attribute(&GlEngine::ShaderFactory::attr_Spotlight)
        ->Attribute(&attr_PhongFog)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Texture, fenceTex)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, Vector<3> { 0.9f, 0.9f, 0.9f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Shininess, 5.0)
        ->Create();
    fenceGfx->SetMaterial(fenceMaterial);
    for (auto provider : providers)
        fenceGfx->AddPropertyProvider(provider);
    pageGobj->AddComponent(fenceGfx);

    return pageGobj;
}
