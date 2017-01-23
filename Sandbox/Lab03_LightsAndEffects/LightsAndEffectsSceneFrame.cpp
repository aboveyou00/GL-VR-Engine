#include "stdafx.h"
#include "LightsAndEffectsSceneFrame.h"
//#include "PhongTorus.h"
//#include "NoLidTeapot.h"
//#include "DiscardTorus.h"
#include "CameraGameObject.h"
#include "../CameraTargetObject.h"
#include "../LightSourceObject.h"
#include "../LabControls.h"

LightsAndEffectsSceneFrame::LightsAndEffectsSceneFrame()
{
}
LightsAndEffectsSceneFrame::~LightsAndEffectsSceneFrame()
{
}

bool LightsAndEffectsSceneFrame::Initialize()
{
    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    CreateGameObject<LabControls>();

    //auto lightSource1 = CreateGameObject<LightSourceObject>();
    //auto torus1 = CreateGameObject<PhongTorus>(Vector<3> { 1, .15f, .3f }, Vector<3> { .4f, .6f, .6f }, lightSource1->lightSource(), Vector<3> { 0, 0, 1 });
    //torus1->SetPosition({ 0, 0, 0 });

    //auto lightSource2 = CreateGameObject<LightSourceObject>();
    //auto torus2 = CreateGameObject<PhongTorus>(Vector<3> { .2f, .6f, .75f }, Vector<3> { .05f, .05f, .05f }, lightSource2->lightSource(), Vector<3> { 1, 0, 0 });
    //torus2->SetPosition({ -5, 0, -5 });

    //auto lightSource3 = CreateGameObject<LightSourceObject>();
    //auto torus3 = CreateGameObject<PhongTorus>(Vector<3> { .4f, .4f, .4f }, Vector<3> { .9f, .9f, .9f }, lightSource3->lightSource(), Vector<3> { 0, 1, 0 }, 3.f, .5f, true);
    //torus3->SetPosition({ 5, 0, -5 });

    //auto lightSource4 = CreateGameObject<LightSourceObject>();
    //auto teapot = CreateGameObject<NoLidTeapot>(Vector<3> { .4f, .4f, .4f }, Vector<3> { .9f, .9f, .9f }, lightSource4->lightSource(), Vector<3> { 0, 1, 0 });
    //teapot->SetPosition({ 7, 0, 2 });

    //auto lightSource5 = CreateGameObject<LightSourceObject>();
    //auto discard = CreateGameObject<DiscardTorus>(Vector<3> { .7f, .0f, .9f }, Vector<3> { .9f, .9f, .9f }, lightSource5->lightSource(), Vector<3> { 1, 0, 0 });
    //discard->SetPosition({ -7, 0, 2 });

    return true;
}
