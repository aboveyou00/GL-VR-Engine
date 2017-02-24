#include "stdafx.h"
#include "ParticlesSceneFrame.h"

#include "../CameraTargetComponent.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "../LabControlsComponent.h"

ParticlesSceneFrame::ParticlesSceneFrame()
{
}
ParticlesSceneFrame::~ParticlesSceneFrame()
{
}

bool ParticlesSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    auto cameraTarget = CameraTargetComponent::Create(this, "CameraTarget");

    auto cameraObject = GlEngine::CameraComponent::Create(this, "Camera");
    cameraObject->transform.position = { 0, -3.5, 7 };

    auto cameraComponent = CreateDefaultCamera();
    cameraComponent->SetTargetObject(cameraTarget);
    cameraComponent->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraComponent->SetClearColor({ .4, .4, .4 });

    auto controls = new GlEngine::GameObject(this, "Lab5ControlsComponent");
    auto controlsComponent = new LabControlsComponent();
    controls->AddComponent(controlsComponent);

    return true;
}
