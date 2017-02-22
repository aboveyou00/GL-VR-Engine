#include "stdafx.h"
#include "DiffuseSceneFrame.h"
#include "CameraComponent.h"
#include "PointLightSource.h"
#include "../OrbitingLight.h"
#include "../CameraTargetComponent.h"
#include "../LightSourceObject.h"
#include "../LabControlsComponent.h"

//HACK HACK HACK
#include "../Sandbox.h"
#include "RenderTarget.h"

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

    auto cameraTarget = CameraTargetComponent::Create(this, "CameraTarget");

    auto cameraObject = GlEngine::CameraComponent::Create(this, "Camera");
    cameraObject->transform.position = { 0, -3.5, 7 };

    auto cameraComponent = cameraObject->component<GlEngine::CameraComponent>();
    cameraComponent->SetTargetObject(cameraTarget);
    cameraComponent->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    Sandbox::windowRenderTarget->SetCamera(cameraComponent);

    auto controls = new GlEngine::GameObject(this, "LabControlsComponent");
    controls->AddComponent(new LabControlsComponent());

    auto lightSource1 = PointLightSourceObject::Create(this, "LightSource1");
    lightSource1;
    //auto pointLight1 = lightSource1->component<PointLightSourceObject>()->lightSource();
    //auto torus1 = OrbitingLight::Create(this, "Torus1", { 1, 1, 1 }, { 0.f, 0.f, .9f }, pointLight1, { 0, 0, 1 });
    //torus1->transform.SetPosition({ 0, 0, 0 });

    //auto lightSource2 = PointLightSourceObject::Create(this, "LightSource2");
    //auto pointLight2 = lightSource2->component<PointLightSourceObject>()->lightSource();
    //auto torus2 = OrbitingLight::Create(this, "Torus2", { 1, 1, 1 }, { .9f, .9f, 0.f }, pointLight2, { 1, 0, 0 });
    //torus2->transform.SetPosition({ -5, 0, -5 });

    //auto lightSource3 = PointLightSourceObject::Create(this, "LightSource3");
    //auto pointLight3 = lightSource3->component<PointLightSourceObject>()->lightSource();
    //auto torus3 = OrbitingLight::Create(this, "Torus3", { 1, 1, 1 }, { .75f, .75f, .75f }, pointLight3, { 0, 1, 0 });
    //torus3->transform.SetPosition({ 5, 0, -5 });

    return true;
}
