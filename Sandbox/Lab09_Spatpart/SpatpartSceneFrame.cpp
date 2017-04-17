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
#include "NullSpatialPartitions.h"
#include "GridSpatialPartitions.h"
#include "OctreeSpatialPartitions.h"
#include "ObjLoader.h"

#include "CrosshairGraphicsObject.h"

const Vector<3> RAYCAST_HIT_COLOR = { 0, 1, 0 };
const Vector<3> RAYCAST_MISS_COLOR = { 1, 0, 0 };

SpatpartSceneFrame::SpatpartSceneFrame()
    : cameraComponent(nullptr), flagGobj(nullptr), renderer(nullptr)
{
}
SpatpartSceneFrame::~SpatpartSceneFrame()
{
}

bool SpatpartSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;
    CreateSpatialPartitions<GlEngine::OctreeSpatialPartitions>(Vector<3>{20, 20, 20}, Vector<3>{0, 0, 0}, 5, 20);
    //CreateSpatialPartitions<GlEngine::GridSpatialPartitions>(Vector<3>{5, 5, 5});
    //CreateSpatialPartitions<GlEngine::NullSpatialPartitions>();

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

    flagGobj = new GlEngine::GameObject(this, "Flag");
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

    auto dragonGobj = new GlEngine::GameObject(this, "Dragon");
    dragonGobj->globalTransform()->SetPosition({ 5, 0, 5 });
    auto dragonObjLoader = new GlEngine::ObjLoader("Resources/dragon.obj", { ambient, light }, GlEngine::ObjLoaderFlag::Graphics);
    dragonObjLoader->OverrideMaterial(new GlEngine::PhongMaterial({ .9f, .3f, .5f }, { .9f, .9f, .9f }, 5.0f));
    dragonGobj->AddComponent(dragonObjLoader);

    for (size_t q = 0; q < TEST_POINT_COUNT; q++)
    {
        auto testPtObj = new GlEngine::GameObject(this, "RaytraceTestPoint");
        testPtObj->AddComponent(new CrosshairGraphicsObject(.2f, Vector<3> { 0, 0, 1.f }));
        testPtObj->Deactivate();
        raytraceDebugObjects[q] = testPtObj;
    }

    auto treeMat = new GlEngine::PhongMaterial({ .0f, .6f, .0f }, { .9f, .9f, .9f }, 5.0f);
    for (int q = -2; q <= 2; q++) {
        for (int w = -2; w <= 2; w++) {
            auto treeGobj = new GlEngine::GameObject(this, "Tree"s);
            auto treeObjLoader = new GlEngine::ObjLoader("Resources/tree.obj", { ambient, light }, GlEngine::ObjLoaderFlag::Graphics);
            treeGobj->globalTransform()->SetPosition({ (q * 10) + 2, 0, (w * 10) + 2 });
            treeObjLoader->OverrideMaterial(treeMat);
            treeGobj->AddComponent(treeObjLoader);
        }
    }

    return true;
}
void SpatpartSceneFrame::Tick(float dt)
{
    Frame::Tick(dt);
    bool hitFlag = false;
    float distance = 0;

    for (size_t q = 0; q < TEST_POINT_COUNT; q++)
    {
        auto ray = cameraComponent->rayToPoint(testPoints[q]);
        auto result = spatialPartitions->RayCast(ray, &distance);
        if (result != nullptr)
        {
            raytraceDebugObjects[q]->Activate();
            raytraceDebugObjects[q]->localTransform()->SetPosition(ray.origin + distance * ray.direction);
        }
        else raytraceDebugObjects[q]->Deactivate();
        hitFlag = hitFlag || (result != nullptr && result->gameObject() == flagGobj);
    }
    this->mainPipeline()->SetClearColor(hitFlag ? RAYCAST_HIT_COLOR : RAYCAST_MISS_COLOR);
}

void SpatpartSceneFrame::UpdateGraphics()
{
    Frame::UpdateGraphics();
    if (renderer != nullptr) return;
    renderer = new FIG::FontRenderer(new FIG::Font("/Windows/Fonts/consola.ttf"), FIG::FontRendererSettings(12));
}

void SpatpartSceneFrame::Render(GlEngine::RenderStage *stage)
{
    Frame::Render(stage);
    if (stage != GlEngine::renderStage_2d) return;
    renderText = "[Disabled]";//spatialPartitions->debugString(cameraComponent->gameObject()->globalTransform()->position());
    renderer->DrawDirect(10, 62, renderText.c_str());
}
