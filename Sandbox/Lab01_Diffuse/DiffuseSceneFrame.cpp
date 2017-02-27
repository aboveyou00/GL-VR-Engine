#include "stdafx.h"
#include "DiffuseSceneFrame.h"
#include "CameraComponent.h"
#include "PointLightSource.h"
#include "../OrbitingLight.h"
#include "../CameraTargetComponent.h"
#include "../LightSourceObject.h"
#include "../LabControlsComponent.h"

typedef GlEngine::PointLightSource PointLightSource;

DiffuseSceneFrame::DiffuseSceneFrame()
{
}
DiffuseSceneFrame::~DiffuseSceneFrame()
{
}

bool DiffuseSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    GlEngine::CameraComponent* cameraComponent;
    auto mainPipeline = CreateDefaultPipeline(cameraComponent);
    mainPipeline->SetClearColor({ .2, .2, .2 });

    auto cameraTarget = new CameraTargetComponent();
    cameraComponent->gameObject()->AddComponent(cameraTarget);

    auto controls = new GlEngine::GameObject(this, "LabControlsComponent");
    controls->AddComponent(new LabControlsComponent());

    auto lightSource1 = PointLightSourceObject::Create(this, "LightSource1");
    auto pointLight1 = lightSource1->component<PointLightSourceObject>()->lightSource();
    auto torus1 = OrbitingLight::Create(this, "Torus1", { 1, 1, 1 }, { 0.f, 0.f, .9f }, pointLight1, { 0, 0, 1 });
    torus1->localTransform()->SetPosition({ 0, 0, 0 });

    auto lightSource2 = PointLightSourceObject::Create(this, "LightSource2");
    auto pointLight2 = lightSource2->component<PointLightSourceObject>()->lightSource();
    auto torus2 = OrbitingLight::Create(this, "Torus2", { 1, 1, 1 }, { .9f, .9f, 0.f }, pointLight2, { 1, 0, 0 });
    torus2->localTransform()->SetPosition({ -5, 0, -5 });

    auto lightSource3 = PointLightSourceObject::Create(this, "LightSource3");
    auto pointLight3 = lightSource3->component<PointLightSourceObject>()->lightSource();
    auto torus3 = OrbitingLight::Create(this, "Torus3", { 1, 1, 1 }, { .75f, .75f, .75f }, pointLight3, { 0, 1, 0 });
    torus3->localTransform()->SetPosition({ 5, 0, -5 });

    return true;
}
