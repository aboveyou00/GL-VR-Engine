#include "stdafx.h"
#include "DistortionSceneFrame.h"

#include "../CameraTargetObject.h"
#include "CameraGameObject.h"
#include "../LabControls.h"

#include "../RawGraphicsObject.h"
#include "../TemplateObj.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"

#include "TextureRenderTarget.h"
#include "GraphicsContext.h"

#include "Engine.h"
#include "GraphicsController.h"

#include "../Lab05_Geometry/GeometrySceneFrame.h"

extern std::string distortVertex;
extern std::string distortFragment;

DistortionSceneFrame::DistortionSceneFrame()
{
    props = {
        { 0, &GlEngine::ShaderFactory::prop_GameTime },
        { 1, &GlEngine::ShaderFactory::prop_Texture }
    };

    distortSource = {
        &distortVertex,
        nullptr,
        nullptr,
        nullptr,
        &distortFragment,
    };

    sceneTex = new GlEngine::TextureRenderTarget(1920, 1080 - 60, GlEngine::TextureFlag::Clamp); //GlEngine::Texture::FromFile("Textures/crate_tl.png", GlEngine::TextureFlag::Clamp);
    this->renderedFrame = new GeometrySceneFrame();
    myCtx = new GlEngine::GraphicsContext(this->renderedFrame);
    myCtx->AddRenderTarget(sceneTex);
}
DistortionSceneFrame::~DistortionSceneFrame()
{
    SafeDelete(myCtx);
    SafeDelete(renderedFrame);
    SafeDelete(sceneTex);
}

bool DistortionSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    CreateGameObject<LabControls>();

    CreateGameObject<TemplateObj>(
        [this](TemplateObj *self, GlEngine::GraphicsContext*)
        {
            auto gobj = new RawGraphicsObject(
                "Resources/clip_plane.obj",
                &this->distortSource,
                &this->props
            );
            for (size_t q = 0; q < self->providers().size(); q++)
                gobj->AddPropertyProvider(self->providers()[q]);
            gobj->SetMaterial(&self->material());

            return gobj;
        },
        TemplateMaterial::Factory()
            ->Name("DistortMaterial")
            ->ProvideConst(&GlEngine::ShaderFactory::prop_Texture, sceneTex)
            ->Create()
    );

    GlEngine::Engine::GetInstance().GetGlController().AddGraphicsContext(myCtx);

    return renderedFrame->Initialize();
}
void DistortionSceneFrame::Tick(float delta)
{
    renderedFrame->Tick(delta);
}
void DistortionSceneFrame::Shutdown()
{
    renderedFrame->Shutdown();
}

void DistortionSceneFrame::HandleEvent(GlEngine::Events::Event &evt)
{
    renderedFrame->HandleEvent(evt);
}
