#include "stdafx.h"
#include "WorldEditorFrame.h"
#include "OctreeSpatialPartitions.h"
#include "CameraComponent.h"
#include "CameraTargetComponent.h"
#include "GameObject.h"
#include "LightSourceObject.h"
#include "AmbientLightSource.h"
#include "Texture.h"
#include "PlaneGraphicsObject.h"

WorldEditorFrame::WorldEditorFrame()
{
}
WorldEditorFrame::~WorldEditorFrame()
{
}

bool WorldEditorFrame::Initialize()
{
    if (!Frame::Initialize()) return false;
    CreateSpatialPartitions<GlEngine::OctreeSpatialPartitions>(Vector<3>{20, 20, 20}, Vector<3>{0, 0, 0}, 11, 20);

    GlEngine::CameraComponent *camera;
    auto pipeline = CreateDefaultPipeline(camera);
    pipeline->SetClearColor(Vector<3> { 0, .1f, .5f });

    auto cameraTarget = new CameraTargetComponent();
    camera->gameObject()->AddComponent(cameraTarget);
    camera->gameObject()->localTransform()->SetPosition({ 0, 3.5, 7 });

    auto lightObj = PointLightSourceObject::Create(this, "PointLightSource");
    auto light = lightObj->component<PointLightSourceObject>()->lightSource();
    light->SetPosition({ 0, 10, 0 });
    //controls->SetControllingLight(light);
    auto ambient = new GlEngine::AmbientLightSource({ .2f, .2f, .2f });

    auto grassTex = GlEngine::Texture::FromFile("Textures/grass1.png"s);
    auto groundPlane = new GlEngine::GameObject(this, "Ground");
    const float GROUND_SIZE = 256.f;
    auto groundPlaneGfx = new GlEngine::PlaneGraphicsObject("Plane_Ground", new GlEngine::PhongMaterial(grassTex, { .9f, .9f, .9f }, 5.0f), { GROUND_SIZE, GROUND_SIZE }, { 30.f, 30.f }, { 20, 20 });
    groundPlaneGfx->AddPropertyProvider(ambient);
    groundPlaneGfx->AddPropertyProvider(light);
    groundPlane->AddComponent(groundPlaneGfx);

    return true;
}
