#include "stdafx.h"
#include "SlendermanSceneFrame.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "PlayerControlsComponent.h"
#include "../LabControlsComponent.h"

#include "AmbientLightSource.h"
#include "../LightSourceObject.h"
#include "Texture.h"
#include "PhongMaterial.h"
#include "PlaneGraphicsObject.h"

#include "FlashlightComponent.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "Attribute.h"
#include "FogSource.h"

#include "RawShaderFactory.h"
#include "../RawGraphicsObject.h"
#include "InstancedGraphicsObject.h"
#include "RandomUtils.h"

#include "PageComponent.h"

extern Attribute attr_PhongFog;

extern std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> instancedPhongFogProps;
extern GlEngine::ShaderFactory::ShaderSource instancedPhongFogSource;

SlendermanSceneFrame::SlendermanSceneFrame()
{
}
SlendermanSceneFrame::~SlendermanSceneFrame()
{
}

bool SlendermanSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    GlEngine::CameraComponent* cameraComponent;
    auto pipeline = CreateDefaultPipeline(cameraComponent);
    pipeline->SetClearColor(Vector<3> { 115.f, 92.f, 52.f } / 255.f);

    cameraComponent->gameObject()->localTransform()->SetPosition({ 0, 3.5, 7 });

    auto cameraTarget = new PlayerControlsComponent(6.f);
    cameraComponent->gameObject()->AddComponent(cameraTarget);

    auto flashlightGobj = new GlEngine::GameObject(this, "Flashlight");
    auto flashlightComp = new FlashlightComponent();
    flashlightGobj->AddComponent(flashlightComp);
    flashlightGobj->SetParent(cameraComponent->gameObject());

    auto spotlight = flashlightComp->spotlight();
    auto ambient = new GlEngine::AmbientLightSource({ .25f, .25f, .25f });
    auto fog = new GlEngine::FogSource(10.f, 60.f, { 0.f, 0.f, 0.f, .8f });

    auto grassTex = GlEngine::Texture::FromFile("Textures/grass1.png"s);
    auto groundMaterial = TemplateMaterial::Factory()
        ->Attribute(&GlEngine::ShaderFactory::attr_GlPosition)
        ->Attribute(&GlEngine::ShaderFactory::attr_Phong)
        ->Attribute(&GlEngine::ShaderFactory::attr_TextureBaseColor)
        ->Attribute(&GlEngine::ShaderFactory::attr_Spotlight)
        ->Attribute(&attr_PhongFog)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Texture, grassTex)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, Vector<3> { 0.9f, 0.9f, 0.9f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Shininess, 5.0)
        ->Create();

    auto groundPlane = new GlEngine::GameObject(this, "Ground");
    const float GROUND_SIZE = 1024.f;
    auto groundPlaneGfx = new GlEngine::PlaneGraphicsObject("Plane_Ground", groundMaterial, { GROUND_SIZE, GROUND_SIZE }, { 30.f, 30.f }, { 20, 20 });
    groundPlaneGfx->AddPropertyProvider(ambient);
    groundPlaneGfx->AddPropertyProvider(spotlight);
    groundPlaneGfx->AddPropertyProvider(fog);
    groundPlane->AddComponent(groundPlaneGfx);

    auto singleTree = new RawGraphicsObject("TreeGfx", "Resources/tree.obj", &instancedPhongFogSource, &instancedPhongFogProps);
    singleTree->SetMaterial(TemplateMaterial::Factory()
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Texture, grassTex)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, Vector<3> { 0.9f, 0.9f, 0.9f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Shininess, 5.0)
        ->Create()
    );
    singleTree->AddPropertyProvider(ambient);
    singleTree->AddPropertyProvider(spotlight);
    singleTree->AddPropertyProvider(fog);
    auto instancedTrees = new GlEngine::InstancedGraphicsObject<GlEngine::VboType::Float, Matrix<4, 4>>("InstancedTrees", singleTree, &GlEngine::ShaderFactory::prop_InstanceModelMatrix);
    auto trees = new GlEngine::GameObject(this, "Trees");
    trees->AddComponent(instancedTrees);

    for (size_t q = 0; q < 10; q++)
    {
        for (size_t e = 0; e < 10; e++)
        {
            auto rot = Quaternion<>(GlEngine::Util::random(360deg), Vector<3> { 0, 1, 0 });
            instancedTrees->AddInstance(rot.ToMatrix() * Matrix<4, 4>::TranslateMatrix(Vector<3> { q, 0, e } * -5));
        }
    }
    instancedTrees->Finalize();

    PageComponent::Create(this, 0, { 80.f,  0, 20.f  }, GlEngine::Util::random(360deg), { ambient, spotlight, fog });
    PageComponent::Create(this, 1, { 20.f,  0, 80.f  }, GlEngine::Util::random(360deg), { ambient, spotlight, fog });
    PageComponent::Create(this, 2, { -20.f, 0, 80.f  }, GlEngine::Util::random(360deg), { ambient, spotlight, fog });
    PageComponent::Create(this, 3, { -80.f, 0, 20.f  }, GlEngine::Util::random(360deg), { ambient, spotlight, fog });
    PageComponent::Create(this, 4, { -80.f, 0, -20.f }, GlEngine::Util::random(360deg), { ambient, spotlight, fog });
    PageComponent::Create(this, 5, { -20.f, 0, -80.f }, GlEngine::Util::random(360deg), { ambient, spotlight, fog });
    PageComponent::Create(this, 6, { 20.f,  0, -80.f }, GlEngine::Util::random(360deg), { ambient, spotlight, fog });
    PageComponent::Create(this, 7, { 80.f,  0, -20.f }, GlEngine::Util::random(360deg), { ambient, spotlight, fog });

    return true;
}
