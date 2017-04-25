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
#include "ObjLoader.h"
#include "EditorControllerComponent.h"

WorldEditorFrame::WorldEditorFrame()
{
}
WorldEditorFrame::~WorldEditorFrame()
{
}

bool WorldEditorFrame::Initialize()
{
    if (!Frame::Initialize()) return false;
    CreateSpatialPartitions<GlEngine::OctreeSpatialPartitions>(Vector<3>{20, 20, 20}, Vector<3>{0, 0, 0}, 6, 20);

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

    auto eccGobj = new GlEngine::GameObject(this, "EditorController");
    auto ecc = new EditorControllerComponent({ ambient, light });
    eccGobj->AddComponent(ecc);
    
    //auto danHide = new GlEngine::GameObject(this, "Daniel's Hideout");
    //auto danHideGfx = new GlEngine::ObjLoader("Resources/dan_hide/AIWorld.obj", { ambient, light }, GlEngine::ObjLoaderFlag::Graphics);
    //danHide->AddComponent(danHideGfx);

    return true;
}
