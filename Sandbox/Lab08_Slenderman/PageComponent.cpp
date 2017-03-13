#include "stdafx.h"
#include "PageComponent.h"
#include "GameObject.h"
#include "ObjGraphicsObject.h"
#include "Texture.h"
#include "Attribute.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "RandomUtils.h"
#include "MathUtils.h"

extern Attribute attr_PhongFog;

PageComponent::PageComponent(int pageNumber)
    : GlEngine::GameComponent("Page"), pageNumber(pageNumber)
{
}
PageComponent::~PageComponent()
{
}

GlEngine::GameObject *PageComponent::Create(GlEngine::Frame *frame, int pageNumber, Vector<3> position, float angle, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers)
{
    auto pageGobj = new GlEngine::GameObject(frame, "Page");
    auto transform = pageGobj->localTransform();
    transform->Translate(position);
    transform->RotateY(angle);

    auto pageComp = new PageComponent(pageNumber);
    pageGobj->AddComponent(pageComp);

    auto wallGfx = new GlEngine::ObjGraphicsObject("PageWallGfx", "Resources/page-wall.obj");
    pageComp->wallGfx = wallGfx;
    auto wallTex = GlEngine::Texture::FromFile("Textures/page-wall.png"s);
    auto wallMaterial = TemplateMaterial::Factory()
        ->Attribute(&GlEngine::ShaderFactory::attr_GlPosition)
        ->Attribute(&GlEngine::ShaderFactory::attr_Phong)
        ->Attribute(&GlEngine::ShaderFactory::attr_TextureBaseColor)
        ->Attribute(&GlEngine::ShaderFactory::attr_Spotlight)
        ->Attribute(&attr_PhongFog)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Texture, wallTex)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, Vector<3> { 0.9f, 0.9f, 0.9f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Shininess, 5.0)
        ->Create();
    wallGfx->SetMaterial(wallMaterial);
    for (auto provider : providers)
        wallGfx->AddPropertyProvider(provider);
    pageGobj->AddComponent(wallGfx);

    std::stringstream pagePathStream;
    pagePathStream << "Textures/page"s << pageNumber << ".png"s;

    auto pageGfx = new GlEngine::ObjGraphicsObject("PageGfx", "Resources/page.obj");
    pageComp->pageGfx = pageGfx;
    auto pageTex = GlEngine::Texture::FromFile(pagePathStream.str(), GlEngine::TextureFlag::Translucent);
    auto pageMaterial = TemplateMaterial::Factory()
        ->Attribute(&GlEngine::ShaderFactory::attr_GlPosition)
        ->Attribute(&GlEngine::ShaderFactory::attr_Phong)
        ->Attribute(&GlEngine::ShaderFactory::attr_TextureBaseColor)
        ->Attribute(&GlEngine::ShaderFactory::attr_Spotlight)
        ->Attribute(&attr_PhongFog)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Texture, pageTex)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, Vector<3> { 0.9f, 0.9f, 0.9f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Shininess, 5.0)
        ->Create();
    pageGfx->SetMaterial(pageMaterial);
    for (auto provider : providers)
        pageGfx->AddPropertyProvider(provider);
    pageGobj->AddComponent(pageGfx);

    return pageGobj;
}

void PageComponent::FindPage()
{
    if (isFound) return;
    isFound = true;
    pageGfx->Deactivate();
}
