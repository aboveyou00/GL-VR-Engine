#include "stdafx.h"
#include "SlenderComponent.h"
#include "GameObject.h"
#include "PlaneGraphicsObject.h"

#include "Texture.h"
#include "Attribute.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "RandomUtils.h"
#include "MathUtils.h"

extern Attribute attr_PhongFog;

SlenderComponent::SlenderComponent(GlEngine::GameObject *player)
    : GlEngine::GameComponent("Slender"), player(player)
{
}
SlenderComponent::~SlenderComponent()
{
}

GlEngine::GameObject *SlenderComponent::Create(GlEngine::Frame *frame, GlEngine::GameObject *player, Vector<3> position, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers)
{
    auto pageGobj = new GlEngine::GameObject(frame, "Slender");
    auto transform = pageGobj->localTransform();
    auto rot = Quaternion<>(-90deg, Vector<3> { 1, 0, 0 });
    transform->Translate(position);
    transform->SetOrientation(rot);

    auto pageComp = new SlenderComponent(player);
    pageGobj->AddComponent(pageComp);

    auto slenderTex = GlEngine::Texture::FromFile("Textures/slender.png"s, GlEngine::TextureFlag::Translucent);
    auto slenderMaterial = TemplateMaterial::Factory()
        ->Attribute(&GlEngine::ShaderFactory::attr_GlPosition)
        ->Attribute(&GlEngine::ShaderFactory::attr_Phong)
        ->Attribute(&GlEngine::ShaderFactory::attr_TextureBaseColor)
        ->Attribute(&GlEngine::ShaderFactory::attr_Spotlight)
        ->Attribute(&attr_PhongFog)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Texture, slenderTex)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, Vector<3> { 0.9f, 0.9f, 0.9f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Shininess, 5.0)
        ->Create();
    auto slenderGfx = new GlEngine::PlaneGraphicsObject("SlenderGfx", slenderMaterial, { .8f, 2 }, { 1, 1 }, { 1, 1 });
    for (auto provider : providers)
        slenderGfx->AddPropertyProvider(provider);
    pageGobj->AddComponent(slenderGfx);

    return pageGobj;
}
