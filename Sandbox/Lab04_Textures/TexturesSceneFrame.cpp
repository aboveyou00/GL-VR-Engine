#include "stdafx.h"
#include "TexturesSceneFrame.h"

#include "CameraGameObject.h"
#include "../CameraTargetObject.h"
#include "../LabControls.h"
#include "MathUtils.h"
#include "GraphicsContext.h"

#include "Texture.h"
#include "CubeGameObject.h"
#include "PlaneGameObject.h"
#include "../LightSourceObject.h"
#include "PointLightSource.h"
#include "AmbientLightSource.h"

#include "FrameBufferCubeGameObject.h"

TexturesSceneFrame::TexturesSceneFrame()
{
}
TexturesSceneFrame::~TexturesSceneFrame()
{
}

bool TexturesSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    auto controls = CreateGameObject<LabControls>();

    auto ambient = new GlEngine::AmbientLightSource({ .25f, .25f, .25f });
    auto pointLight = CreateGameObject<PointLightSourceObject>();
    controls->SetControllingLight(pointLight->lightSource());
    pointLight->lightSource()->SetPosition({ 0, 2.5, -2.5 });

    auto crateTex = GlEngine::Texture::FromFile("Textures/crate.png");
    auto cube1 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, crateTex);
    cube1->graphicsObject()->AddPropertyProvider(ambient);
    cube1->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    cube1->SetPosition({ -7.5f, 0, 0 });
    cube1->SetRotationSpeed({ 0, 45deg, 0 });

    auto brickTex = GlEngine::Texture::FromFile("Textures/bricks.png");
    auto mossOverlayTex = GlEngine::Texture::FromFile("Textures/moss-overlay.png", GlEngine::TextureFlag::Translucent);
    auto cube2 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, brickTex, mossOverlayTex);
    cube2->graphicsObject()->AddPropertyProvider(ambient);
    cube2->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    cube2->SetPosition({ -2.5f, 0, 0 });
    cube2->SetRotationSpeed({ 0, 45deg, 0 });

    auto cube3 = CreateGameObject<FrameBufferCubeGameObject>(Vector<3> { 3, 3, 3 });
    cube3->graphicsObject()->AddPropertyProvider(ambient);
    cube3->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    cube3->SetPosition({ 2.5f, 0, 0 });
    cube3->SetRotationSpeed({ 0, 45deg, 0 });

    auto leafMaskTex = GlEngine::Texture::FromFile("Textures/leaf-mask.png", GlEngine::TextureFlag::AlphaMap);
    auto cube4 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, crateTex, leafMaskTex);
    cube4->graphicsObject()->AddPropertyProvider(ambient);
    cube4->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    cube4->SetPosition({ 7.5f, 0, 0 });
    cube4->SetRotationSpeed({ 0, 45deg, 0 });

    auto crateNormalMask = GlEngine::Texture::FromFile("Textures/crate-normals.png", GlEngine::TextureFlag::NormalMask);
    auto plane1 = CreateGameObject<GlEngine::PlaneGameObject>(Vector<2> { 16, 16 }, Vector<2> { 1, 1 }, crateTex, crateNormalMask);
    plane1->graphicsObject()->AddPropertyProvider(ambient);
    plane1->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    plane1->SetPosition({ 0, -3.f, 0 });

    return true;
}
