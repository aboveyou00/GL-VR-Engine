#include "stdafx.h"
#include "SpatpartSceneFrame.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "FirstPersonControlsComponent.h"
#include "../LabControlsComponent.h"

#include "AmbientLightSource.h"
#include "../LightSourceObject.h"
#include "Texture.h"
#include "PhongMaterial.h"
#include "PlaneGraphicsObject.h"

#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "Attribute.h"
#include "FogSource.h"

#include "RawShaderFactory.h"
#include "../RawGraphicsObject.h"
#include "InstancedGraphicsObject.h"
#include "RandomUtils.h"

#include "ObjLoader.h"

SpatpartSceneFrame::SpatpartSceneFrame()
{
}
SpatpartSceneFrame::~SpatpartSceneFrame()
{
}

bool SpatpartSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    GlEngine::CameraComponent* cameraComponent;
    auto pipeline = CreateDefaultPipeline(cameraComponent);
    pipeline->SetClearColor(Vector<3> { 0, .1f, .5f });

    cameraComponent->gameObject()->localTransform()->SetPosition({ 0, 3.5, 7 });

    auto cameraTarget = new FirstPersonControlsComponent(6.f);
    cameraComponent->gameObject()->AddComponent(cameraTarget);

    auto controls = new GlEngine::GameObject(this, "LabControlsComponent");
    auto controlsComponent = new LabControlsComponent();
    controls->AddComponent(controlsComponent);

    auto lightObj = PointLightSourceObject::Create(this, "PointLightSource");
    auto light = lightObj->component<PointLightSourceObject>()->lightSource();
    light->SetPosition({ 0, 10, 0 });
    controlsComponent->SetControllingLight(light);
    auto ambient = new GlEngine::AmbientLightSource({ .2f, .2f, .2f });

    auto grassTex = GlEngine::Texture::FromFile("Textures/grass1.png"s);
    auto groundPlane = new GlEngine::GameObject(this, "Ground");
    const float GROUND_SIZE = 256.f;
    auto groundPlaneGfx = new GlEngine::PlaneGraphicsObject("Plane_Ground", new GlEngine::PhongMaterial(grassTex, { .9f, .9f, .9f }, 5.0f), { GROUND_SIZE, GROUND_SIZE }, { 30.f, 30.f }, { 20, 20 });
    groundPlaneGfx->AddPropertyProvider(ambient);
    groundPlaneGfx->AddPropertyProvider(light);
    groundPlane->AddComponent(groundPlaneGfx);

    auto flagGobj = new GlEngine::GameObject(this, "Flag");
    auto objLoader = new GlEngine::ObjLoader("Resources/flag.obj", { ambient, light }, GlEngine::ObjLoaderFlag::Graphics);
    objLoader->OverrideMaterial(new GlEngine::PhongMaterial({ 1.f, .2f, .2f }, { .9f, .9f, .9f }, 5.0f));
    flagGobj->AddComponent(objLoader);

    GlEngine::GameObject *wallGobj;
    GlEngine::ObjLoader *wallObjLoader;

    wallGobj = new GlEngine::GameObject(this, "HexWall1");
    wallObjLoader = new GlEngine::ObjLoader("Resources/hex-wall-window.obj", { ambient, light }, GlEngine::ObjLoaderFlag::Graphics);
    wallObjLoader->OverrideMaterial(new GlEngine::PhongMaterial({ .2f, .4f, .8f }, { .9f, .9f, .9f }, 5.0f));
    wallGobj->AddComponent(wallObjLoader);

    wallGobj = new GlEngine::GameObject(this, "HexWall2");
    wallObjLoader = new GlEngine::ObjLoader("Resources/hex-wall-2.obj", { ambient, light }, GlEngine::ObjLoaderFlag::Graphics);
    wallObjLoader->OverrideMaterial(new GlEngine::PhongMaterial({ .8f, .2f, .4f }, { .9f, .9f, .9f }, 5.0f));
    wallGobj->AddComponent(wallObjLoader);

    wallGobj = new GlEngine::GameObject(this, "HexWall3");
    wallObjLoader = new GlEngine::ObjLoader("Resources/hex-wall-3.obj", { ambient, light }, GlEngine::ObjLoaderFlag::Graphics);
    wallObjLoader->OverrideMaterial(new GlEngine::PhongMaterial({ .4f, .8f, .2f }, { .9f, .9f, .9f }, 5.0f));
    wallGobj->AddComponent(wallObjLoader);

    return true;
}
void SpatpartSceneFrame::Tick(float dt)
{
    Frame::Tick(dt);
    float distance = 0;
    auto result = spatialPartitions->RayCast(cameraComponent->centerRay(), &distance);
    GlEngine::Util::Log("Raycast object: %d, distance: %f", result, distance);
}