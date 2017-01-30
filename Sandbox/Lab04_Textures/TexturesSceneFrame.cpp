#include "stdafx.h"
#include "TexturesSceneFrame.h"

#include "CameraGameObject.h"
#include "../CameraTargetObject.h"
#include "../LabControls.h"
#include "MathUtils.h"

#include "Texture.h"
#include "CubeGameObject.h"
#include "../LightSourceObject.h"
#include "PointLightSource.h"
#include "AmbientLightSource.h"

TexturesSceneFrame::TexturesSceneFrame()
{
}
TexturesSceneFrame::~TexturesSceneFrame()
{
}

bool TexturesSceneFrame::Initialize()
{
    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    CreateGameObject<LabControls>();

    auto ambient = new GlEngine::AmbientLightSource({ .25f, .25f, .25f });
    auto pointLight = CreateGameObject<PointLightSourceObject>();
    pointLight->lightSource()->SetPosition({ 0, 2.5, -2.5 });

    auto crateTex = GlEngine::Texture::FromFile("Textures/crate.png");
    auto cube1 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, crateTex);
    cube1->graphicsObject()->AddPropertyProvider(ambient);
    cube1->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    cube1->SetPosition({ -5, 0, 0 });
    cube1->SetRotationSpeed({ 0, 45deg, 0 });

    auto brickTex = GlEngine::Texture::FromFile("Textures/bricks.png");
    auto mossOverlayTex = GlEngine::Texture::FromFile("Textures/moss-overlay.png", GlEngine::TextureFlag::Translucent);
    auto cube2 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, brickTex, mossOverlayTex);
    cube2->graphicsObject()->AddPropertyProvider(ambient);
    cube2->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    cube2->SetPosition({ 0, 0, 0 });
    cube2->SetRotationSpeed({ 0, 45deg, 0 });

    auto leafMaskTex = GlEngine::Texture::FromFile("Textures/leaf-mask.png", GlEngine::TextureFlag::AlphaMap);
    auto cube3 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, crateTex, leafMaskTex);
    cube3->graphicsObject()->AddPropertyProvider(ambient);
    cube3->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    cube3->SetPosition({ 5, 0, 0 });
    cube3->SetRotationSpeed({ 0, 45deg, 0 });

    return true;
}
