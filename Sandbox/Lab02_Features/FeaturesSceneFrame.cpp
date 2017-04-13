#include "stdafx.h"
#include "FeaturesSceneFrame.h"

#include "CameraComponent.h"
#include "../CameraTargetComponent.h"
#include "../LightSourceObject.h"
#include "../LabControlsComponent.h"

#include "../OrbitingLight.h"
#include "DiscardPhongMaterial.h"
#include "PhongFlatMaterial.h"

#include "AmbientLightSource.h"

typedef GlEngine::PointLightSource PointLightSource;

FeaturesSceneFrame::FeaturesSceneFrame()
{
}
FeaturesSceneFrame::~FeaturesSceneFrame()
{
}

bool FeaturesSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    GlEngine::CameraComponent* cameraComponent;
    auto mainPipeline = CreateDefaultPipeline(cameraComponent);
    mainPipeline->SetClearColor({ .1, .1, .3 });

    auto cameraTarget = new CameraTargetComponent();
    cameraComponent->gameObject()->AddComponent(cameraTarget);
    cameraComponent->gameObject()->localTransform()->SetPosition({ 0, 3.5, 7 });

    auto controls = new GlEngine::GameObject(this, "LabControlsComponent");
    controls->AddComponent(new LabControlsComponent());

    auto ambient = new GlEngine::AmbientLightSource({ .1f, .1f, .1f });

    auto lightSource1 = PointLightSourceObject::Create(this, "LightSource1");
    auto pointLight1 = lightSource1->component<PointLightSourceObject>()->lightSource();
    auto phongMat1 = new GlEngine::PhongMaterial({ 1, .15f, .3f }, { .4f, .6f, .6f });
    auto torus1 = OrbitingLight::Create(this, "PhongTorus1", phongMat1, pointLight1, { 0, 0, 1 }, { ambient });
    torus1->localTransform()->SetPosition({ 0, 0, 0 });

    auto lightSource2 = PointLightSourceObject::Create(this, "LightSource2");
    auto pointLight2 = lightSource2->component<PointLightSourceObject>()->lightSource();
    auto phongMat2 = new GlEngine::PhongMaterial({ .2f, .6f, .75f }, { .05f, .05f, .05f });
    auto torus2 = OrbitingLight::Create(this, "PhongTorus2", phongMat2, pointLight2, { 1, 0, 0 }, { ambient });
    torus2->localTransform()->SetPosition({ -5, 0, -5 });

    auto lightSource3 = PointLightSourceObject::Create(this, "LightSource3");
    auto pointLight3 = lightSource3->component<PointLightSourceObject>()->lightSource();
    auto phongMat3 = new PhongFlatMaterial({ .4f, .4f, .4f }, { .9f, .9f, .9f });
    auto torus3 = OrbitingLight::Create(this, "PhongTorus3", phongMat3, pointLight3, { 0, 1, 0 }, { ambient }, 3.f, .5f);
    torus3->localTransform()->SetPosition({ 5, 0, -5 });

    auto lightSource4 = PointLightSourceObject::Create(this, "LightSource4");
    auto pointLight4 = lightSource4->component<PointLightSourceObject>()->lightSource();
    auto phongMat4 = new GlEngine::PhongMaterial({ .4f, .4f, .4f }, { .9f, .9f, .9f });
    auto teapot = OrbitingLight::Create(this, "PhongTorus4", phongMat4, "Resources/teapot.obj", pointLight4, Vector<3> { 0, 1, 0 }, { ambient });
    teapot->localTransform()->SetPosition({ 7, 0, 2 });
    teapot->localTransform()->RotateZ(60deg);

    auto lightSource5 = PointLightSourceObject::Create(this, "LightSource5");
    auto pointLight5 = lightSource5->component<PointLightSourceObject>()->lightSource();
    auto discardMaterial = new DiscardPhongMaterial({ .7f, .0f, .9f }, { .9f, .9f, .9f });
    auto discard = OrbitingLight::Create(this, "DiscardTorus", discardMaterial, pointLight5, { 1, 0, 0 }, { ambient });
    discard->localTransform()->SetPosition({ -7, 0, 2 });

    return true;
}
