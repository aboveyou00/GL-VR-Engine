#include "stdafx.h"
#include "Lab05Frame.h"
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
#include "PathingNodesController.h"
#include "GridGraphicsObject.h"
#include "PathingNodesController.h"

Lab05Frame::Lab05Frame()
{
}
Lab05Frame::~Lab05Frame()
{
}

bool Lab05Frame::Initialize()
{
    if (!Frame::Initialize()) return false;
    CreateSpatialPartitions<GlEngine::OctreeSpatialPartitions>(Vector<3>{20, 20, 20}, Vector<3>{0, 0, 0}, 6, 20);

    GlEngine::CameraComponent *camera;
    auto pipeline = CreateDefaultPipeline(camera);
    pipeline->SetClearColor(Vector<3> { 0, .1f, .5f });

    auto lightObj = PointLightSourceObject::Create(this, "PointLightSource");
    auto light = lightObj->component<PointLightSourceObject>()->lightSource();
    light->SetPosition({ 0, 10, 0 });
    //controls->SetControllingLight(light);
    auto ambient = new GlEngine::AmbientLightSource({ .2f, .2f, .2f });

    auto cameraTarget = new CameraTargetComponent();
    camera->gameObject()->AddComponent(cameraTarget);
    camera->gameObject()->localTransform()->SetPosition({ 0, 3.5, 7 });
    auto ecc = new EditorControllerComponent({ ambient, light }, false);
    camera->gameObject()->AddComponent(ecc);

    auto gridGameObject = new GlEngine::GameObject(this, "Grid");
    gridGameObject->AddComponent(new GridGraphicsObject({ 0, 0, 1, 1 }, { 0, 0, 0 }, { 1, 1 }, { 20, 20 }));

    auto pathingNodesObj = new GlEngine::GameObject(this, "PathingNodesObject");
    auto pathingNodes = new PathingNodesController({ ambient, light }, true, camera);
    pathingNodesObj->AddComponent(pathingNodes);

    return true;
}
