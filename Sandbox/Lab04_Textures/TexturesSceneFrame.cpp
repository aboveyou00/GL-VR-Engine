#include "stdafx.h"
#include "TexturesSceneFrame.h"

#include "CameraComponent.h"
#include "../CameraTargetComponent.h"
#include "../LabControlsComponent.h"
#include "MathUtils.h"

#include "Texture.h"
#include "CubeGraphicsObject.h"
#include "PlaneGraphicsObject.h"
#include "../LightSourceObject.h"
#include "PointLightSource.h"
#include "AmbientLightSource.h"

#include "../FixedRotationComponent.h"
#include "TextureRenderTarget.h"
#include "SimpleRenderPipeline.h"
#include "PerspectiveViewPort.h"
#include "OrthoViewPort.h"

TexturesSceneFrame::TexturesSceneFrame()
{
}
TexturesSceneFrame::~TexturesSceneFrame()
{
}

bool TexturesSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    GlEngine::CameraComponent* cameraComponent;
    auto mainPipeline = CreateDefaultPipeline(cameraComponent);
    mainPipeline->SetClearColor({ .3, .1, .1 });
    cameraComponent->gameObject()->localTransform()->SetPosition({ 0, 3.5, 7 });

    auto cameraTarget = new CameraTargetComponent();
    cameraComponent->gameObject()->AddComponent(cameraTarget);

    auto controls = new GlEngine::GameObject(this, "Lab5ControlsComponent");
    auto controlsComponent = new LabControlsComponent();
    controls->AddComponent(controlsComponent);

    auto ambient = new GlEngine::AmbientLightSource({ .25f, .25f, .25f });
    auto pointLight = PointLightSourceObject::Create(this, "PointLight1");
    auto lightSource = pointLight->component<PointLightSourceObject>()->lightSource();
    controlsComponent->SetControllingLight(lightSource);
    lightSource->SetPosition({ 0, 2.5, -2.5 });

    auto crateTex = GlEngine::Texture::FromFile("Textures/crate.png"s);
    auto cube1 = new GlEngine::GameObject(this, "Cube1");
    auto mat1 = new GlEngine::PhongMaterial(crateTex);
    auto cubeGfx1 = new GlEngine::CubeGraphicsObject("Cube1_Gfx", mat1, { 3, 3, 3 });
    cubeGfx1->AddPropertyProvider(ambient);
    cubeGfx1->AddPropertyProvider(lightSource);
    cube1->AddComponent(cubeGfx1);
    cube1->localTransform()->SetPosition({ -7.5f, 0, 0 });
    cube1->AddComponent(new FixedRotationComponent({ 0, 45deg, 0 }));

    auto brickTex = GlEngine::Texture::FromFile("Textures/bricks.png"s);
    auto mossOverlayTex = GlEngine::Texture::FromFile("Textures/moss-overlay.png"s, GlEngine::TextureFlag::Translucent);
    auto cube2 = new GlEngine::GameObject(this, "Cube2");
    auto mat2 = new GlEngine::PhongMaterial(brickTex, mossOverlayTex);
    auto cubeGfx2 = new GlEngine::CubeGraphicsObject("Cube2_Gfx", mat2, { 3, 3, 3 });
    cubeGfx2->AddPropertyProvider(ambient);
    cubeGfx2->AddPropertyProvider(lightSource);
    cube2->AddComponent(cubeGfx2);
    cube2->localTransform()->SetPosition({ -2.5f, 0, 0 });
    cube2->AddComponent(new FixedRotationComponent({ 0, 45deg, 0 }));

    auto texRenderTarget = new GlEngine::TextureRenderTarget(512, 512);
    auto trCamera = GlEngine::CameraComponent::Create(this, "TexRTCamera");
    trCamera->SetParent(cameraComponent->gameObject());
    auto trCameraC = trCamera->component<GlEngine::CameraComponent>();
    
    auto trPipeline = new GlEngine::SimpleRenderPipeline(this, { 
        { GlEngine::renderStage_opaque, trCameraC },
        { GlEngine::renderStage_translucent, trCameraC },
        { GlEngine::renderStage_2d, trCameraC }
    });

    trPipeline->SetClearColor({ .1, .3, .1 });
    texRenderTarget->SetRenderPipeline(trPipeline);
    texRenderTarget->SetViewPort(GlEngine::renderStage_opaque, new GlEngine::PerspectiveViewPort());
    texRenderTarget->SetViewPort(GlEngine::renderStage_translucent, new GlEngine::PerspectiveViewPort());
    texRenderTarget->SetViewPort(GlEngine::renderStage_2d, new GlEngine::OrthoViewPort());
    texRenderTarget->AddToGraphicsLoop();

    auto cube3 = new GlEngine::GameObject(this, "Cube3");
    auto mat3 = new GlEngine::PhongMaterial(texRenderTarget);
    auto cubeGfx3 = new GlEngine::CubeGraphicsObject("Cube3_Gfx", mat3, { 3, 3, 3 });
    cubeGfx3->AddPropertyProvider(ambient);
    cubeGfx3->AddPropertyProvider(lightSource);
    cube3->AddComponent(cubeGfx3);
    cube3->localTransform()->SetPosition({ 2.5f, 0, 0 });
    cube3->AddComponent(new FixedRotationComponent({ 0, 45deg, 0 }));

    auto leafMaskTex = GlEngine::Texture::FromFile("Textures/leaf-mask.png"s, GlEngine::TextureFlag::AlphaMap);
    auto cube4 = new GlEngine::GameObject(this, "Cube4");
    auto mat4 = new GlEngine::PhongMaterial(crateTex, leafMaskTex);
    auto cubeGfx4 = new GlEngine::CubeGraphicsObject("Cube4_Gfx", mat4, { 3, 3, 3 });
    cubeGfx4->AddPropertyProvider(ambient);
    cubeGfx4->AddPropertyProvider(lightSource);
    cube4->AddComponent(cubeGfx4);
    cube4->localTransform()->SetPosition({ 7.5f, 0, 0 });
    cube4->AddComponent(new FixedRotationComponent({ 0, 45deg, 0 }));

    auto crateNormalMask = GlEngine::Texture::FromFile("Textures/crate-normals.png"s, GlEngine::TextureFlag::NormalMask);
    auto plane1 = new GlEngine::GameObject(this, "NormalMapPlane");
    auto planeMat1 = new GlEngine::PhongMaterial(crateTex, crateNormalMask);
    auto planeGfx1 = new GlEngine::PlaneGraphicsObject("Plane1_Gfx", planeMat1, { 16, 16 }, { 1, 1 });
    planeGfx1->AddPropertyProvider(ambient);
    planeGfx1->AddPropertyProvider(lightSource);
    plane1->AddComponent(planeGfx1);
    plane1->localTransform()->SetPosition({ 0, -3.f, 0 });

    return true;
}
