#include "stdafx.h"
#include "DiffuseSceneFrame.h"
#include "LitTorus.h"
#include "CameraGameObject.h"
#include "../CameraTargetObject.h"
#include "../LightSourceObject.h"
#include "../LabControls.h"
#include "PointLightSource.h"

typedef GlEngine::PointLightSource PointLightSource;

DiffuseSceneFrame::DiffuseSceneFrame()
{
}
DiffuseSceneFrame::~DiffuseSceneFrame()
{
}

bool DiffuseSceneFrame::Initialize()
{
    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    CreateGameObject<LabControls>();

    auto lightSource1 = CreateGameObject<LightSourceObject<PointLightSource>>(new PointLightSource());
    auto torus1 = CreateGameObject<LitTorus>(Vector<3> { 1, 1, 1 }, Vector<3> { 0.f, 0.f, .9f }, lightSource1->lightSource(), Vector<3> { 0, 0, 1 });
    torus1->SetPosition({ 0, 0, 0 });

    auto lightSource2 = CreateGameObject<LightSourceObject<PointLightSource>>(new PointLightSource());
    auto torus2 = CreateGameObject<LitTorus>(Vector<3> { 1, 1, 1 }, Vector<3> { .9f, .9f, 0.f }, lightSource2->lightSource(), Vector<3> { 1, 0, 0 });
    torus2->SetPosition({ -5, 0, -5 });

    auto lightSource3 = CreateGameObject<LightSourceObject<PointLightSource>>(new PointLightSource());
    auto torus3 = CreateGameObject<LitTorus>(Vector<3> { 1, 1, 1 }, Vector<3> { .75f, .75f, .75f }, lightSource3->lightSource(), Vector<3> { 0, 1, 0 });
    torus3->SetPosition({ 5, 0, -5 });

    return true;
}
