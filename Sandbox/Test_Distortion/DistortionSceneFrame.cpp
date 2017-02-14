#include "stdafx.h"
#include "DistortionSceneFrame.h"

#include "../CameraTargetObject.h"
#include "CameraGameObject.h"
#include "../LabControls.h"

#include "../RawGraphicsObject.h"
#include "../TemplateObj.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"

#include "VboGraphicsObject.h"

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

    sceneTex = GlEngine::Texture::FromFile("Textures/crate_tl.png");
}
DistortionSceneFrame::~DistortionSceneFrame()
{
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
            ->Provide(&GlEngine::ShaderFactory::prop_Texture, sceneTex)
            ->Create()
    );

    return true;
}
