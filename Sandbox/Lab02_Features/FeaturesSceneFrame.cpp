#include "stdafx.h"
#include "FeaturesSceneFrame.h"
#include "PhongTorus.h"
#include "NoLidTeapot.h"
#include "CameraGameObject.h"
#include "../CameraTargetObject.h"
#include "../LightSourceObject.h"

FeaturesSceneFrame::FeaturesSceneFrame()
{
}
FeaturesSceneFrame::~FeaturesSceneFrame()
{
}

bool FeaturesSceneFrame::Initialize()
{
    auto testObject = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(testObject);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    auto lightSource1 = CreateGameObject<LightSourceObject>();
    auto torus1 = CreateGameObject<PhongTorus>(Vector<3> { 1, .15f, .3f }, Vector<3> { .4f, .6f, .6f }, lightSource1->lightSource(), Vector<3> { 0, 0, 1 });
    torus1->SetPosition({ 0, 0, 0 });

    auto lightSource2 = CreateGameObject<LightSourceObject>();
    auto torus2 = CreateGameObject<PhongTorus>(Vector<3> { .2f, .6f, .75f }, Vector<3> { .05f, .05f, .05f }, lightSource2->lightSource(), Vector<3> { 1, 0, 0 });
    torus2->SetPosition({ -5, 0, -5 });

    auto lightSource3 = CreateGameObject<LightSourceObject>();
    auto torus3 = CreateGameObject<PhongTorus>(Vector<3> { .4f, .4f, .4f }, Vector<3> { .9f, .9f, .9f }, lightSource3->lightSource(), Vector<3> { 0, 1, 0 });
    torus3->SetPosition({ 5, 0, -5 });

    auto lightSource4 = CreateGameObject<LightSourceObject>();
    auto teapot = CreateGameObject<NoLidTeapot>(Vector<3> { .4f, .4f, .4f }, Vector<3> { .9f, .9f, .9f }, lightSource4->lightSource(), Vector<3> { 0, 1, 0 });
    teapot->SetPosition({ 7, 0, 2 });

    return true;
}
