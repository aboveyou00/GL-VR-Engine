#include "stdafx.h"
#include "DiffuseSceneFrame.h"
#include "LitTorus.h"
#include "CameraGameObject.h"
#include "CameraTargetObject.h"

DiffuseSceneFrame::DiffuseSceneFrame()
{
}
DiffuseSceneFrame::~DiffuseSceneFrame()
{
}

bool DiffuseSceneFrame::Initialize()
{
    auto testObject = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(testObject);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    auto torus1 = CreateGameObject<LitTorus>(Vector<3> { 1, 1, 1 }, 1.f);
    torus1->SetPosition({ 0, 0, 0 });

    auto torus2 = CreateGameObject<LitTorus>(Vector<3> { 1, 1, 1 }, 1.f);
    torus2->SetPosition({ -5, 0, -5 });

    auto torus3 = CreateGameObject<LitTorus>(Vector<3> { 1, 1, 1 }, 1.f);
    torus3->SetPosition({ 5, 0, -5 });

    //auto camera = CreateGameObject<GlEngine::CameraGameObject>();
    //camera->SetTargetObject(torus1);
    //camera->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    //camera->SetPosition({ 0, -35, 70 });

    return true;
}
