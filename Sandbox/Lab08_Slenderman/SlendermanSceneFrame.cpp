#include "stdafx.h"
#include "SlendermanSceneFrame.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "../CameraTargetComponent.h"
#include "../LabControlsComponent.h"

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

    auto cameraTarget = new CameraTargetComponent();
    cameraComponent->gameObject()->AddComponent(cameraTarget);

    auto controls = new GlEngine::GameObject(this, "LabControlsComponent");
    auto controlsComponent = new LabControlsComponent();
    controls->AddComponent(controlsComponent);



    return true;
}
