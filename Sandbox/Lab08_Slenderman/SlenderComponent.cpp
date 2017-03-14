#include "stdafx.h"
#include "SlenderComponent.h"
#include "GameObject.h"
#include "ObjGraphicsObject.h"

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
    transform->Translate(position);

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
    auto slenderGfx = new GlEngine::ObjGraphicsObject("SlenderGfx", "Resources/slender.obj"s);
    slenderGfx->SetMaterial(slenderMaterial);
    for (auto provider : providers)
        slenderGfx->AddPropertyProvider(provider);
    pageGobj->AddComponent(slenderGfx);

    return pageGobj;
}

void SlenderComponent::Tick(float delta)
{
    GameComponent::Tick(delta);

    Vector<3> diff = gameObject()->localTransform()->position() - player->localTransform()->position();
    float direction = atan2(diff[2], -diff[0]);
    auto rot = Quaternion<>(-direction - 90deg, { 0, 1, 0 });
    gameObject()->localTransform()->SetOrientation(rot);
}
