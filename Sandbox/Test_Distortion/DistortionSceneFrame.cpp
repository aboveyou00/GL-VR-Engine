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
#include "KeyboardEvent.h"
#include "GraphicsController.h"
#include "Property.h"
#include "../Lab05_Geometry/GeometrySceneFrame.h"
#include "../Lab04_Textures/TexturesSceneFrame.h"
#include "../Lab03_LightsAndEffects/LightsAndEffectsSceneFrame.h"

extern std::string distortVertex;
extern std::string distortFragment;
static GlEngine::ShaderFactory::Property<GlEngine::ShaderFactory::Subroutine*> prop_Subroutine("__subroutine__");
static GlEngine::ShaderFactory::Property<GlEngine::ShaderFactory::Array<float, 25>> prop_ConvolutionKernel("convolution_kernel");

DistortionSceneFrame::DistortionSceneFrame()
    : pair_index(0)
{
    props = {
        { 0, &GlEngine::ShaderFactory::prop_GameTime },
        { 1, &GlEngine::ShaderFactory::prop_ScreenDimensions },
        { 2, &GlEngine::ShaderFactory::prop_Texture },
        { 3, &prop_ConvolutionKernel },
        { 4, &prop_Subroutine }
    };

    RefreshPair();

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
            ->ProvideArray(&prop_ConvolutionKernel, currentConvolutionKernel)
            ->Provide(&prop_Subroutine, currentSubroutine)
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
    auto *kbdEvt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
    if (kbdEvt != nullptr && kbdEvt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyTyped)
    {
        bool sr_changed = false;
        if (kbdEvt->GetVirtualKeyCode() == VK_SQUARE_BRACKET_RIGHT)
        {
            this->pair_index += 2;
            sr_changed = true;
        }
        else if (kbdEvt->GetVirtualKeyCode() == VK_SQUARE_BRACKET_LEFT)
        {
            this->pair_index -= 2;
            sr_changed = true;
        }
        if (sr_changed)
        {
            RefreshPair();
            kbdEvt->Handle();
        }
    }

    if (!evt.IsHandled()) renderedFrame->HandleEvent(evt);
}

void DistortionSceneFrame::RefreshPair()
{
    if (this->pair_index < 0)
        this->pair_index += PAIR_COUNT * 2;
    this->pair_index %= PAIR_COUNT * 2;

    this->currentSubroutine = subroutines[subroutineKernelPairs[pair_index]];
    this->currentConvolutionKernel = convolutionKernels[subroutineKernelPairs[pair_index + 1]];
    GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting pair to index %d", pair_index);
    GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting subroutine to %s", this->currentSubroutine->name().c_str());
    GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting kernel to index %d", subroutineKernelPairs[pair_index + 1]);
}
