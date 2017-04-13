#include "stdafx.h"
#include "SlendermanStaticSceneFrame.h"

#include "CameraComponent.h"
#include "../CameraTargetComponent.h"
#include "../LabControlsComponent.h"

#include "../RawGraphicsObject.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"

#include "TextureRenderTarget.h"
#include "GameObject.h"
#include "PerspectiveViewPort.h"
#include "OrthoViewPort.h"

#include "Engine.h"
#include "KeyboardEvent.h"
#include "GraphicsController.h"
#include "Property.h"
#include "SlendermanSceneFrame.h"

#include "AmbientLightSource.h"
#include "PointLightSource.h"
#include "PhongMaterial.h"
#include "CubeGraphicsObject.h"
#include "../LightSourceObject.h"
#include "../FixedRotationComponent.h"

#include "ObjLoader.h"
#include "RawShaderFactory.h"

extern GlEngine::ShaderFactory::Property<float> prop_StaticAmount;
extern std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> staticProps;
extern GlEngine::ShaderFactory::ShaderSource staticSource;

SlendermanStaticSceneFrame::SlendermanStaticSceneFrame()
{
}
SlendermanStaticSceneFrame::~SlendermanStaticSceneFrame()
{
    SafeDelete(renderedFrame);
    SafeDelete(sceneTex);
}

bool SlendermanStaticSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    this->renderedFrame = new SlendermanSceneFrame();
    this->renderedFrame->Initialize();

    sceneTex = new GlEngine::TextureRenderTarget(1920, 1080 - 60, GlEngine::TextureFlag::Clamp);
    sceneTex->SetRenderPipeline(this->renderedFrame->mainPipeline());
    sceneTex->SetViewPort(GlEngine::renderStage_opaque, new GlEngine::PerspectiveViewPort());
    sceneTex->SetViewPort(GlEngine::renderStage_translucent, new GlEngine::PerspectiveViewPort());
    sceneTex->SetViewPort(GlEngine::renderStage_2d, new GlEngine::OrthoViewPort());
    sceneTex->AddToGraphicsLoop();

    GlEngine::CameraComponent* cameraComponent;
    auto mainPipeline = CreateDefaultPipeline(cameraComponent);
    mainPipeline->SetClearColor({ .05, .1, .15 });

    auto cameraTarget = new CameraTargetComponent();
    cameraComponent->gameObject()->AddComponent(cameraTarget);

    auto clipPlaneObjLoader = new GlEngine::ObjLoader(
        "Resources/clip_plane.obj",
        {},
        [](GlEngine::Material*) { return new GlEngine::ShaderFactory::RawShaderFactory(&staticSource, &staticProps); },
        GlEngine::ObjLoaderFlag::Graphics
    );
    clipPlaneObjLoader->OverrideMaterial(TemplateMaterial::Factory()
        ->Name("StaticMaterial")
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Texture, sceneTex)
        ->Provide(&prop_StaticAmount, this->renderedFrame->static_amount)
        ->Create()
    );
    auto clipPlane = new GlEngine::GameObject(this, "ClipPlane");
    clipPlane->AddComponent(clipPlaneObjLoader);

    return true;
}
void SlendermanStaticSceneFrame::Tick(float delta)
{
    if (renderedFrame == nullptr) return;
    renderedFrame->Tick(delta);
}
void SlendermanStaticSceneFrame::Shutdown()
{
    if (renderedFrame == nullptr) return;
    renderedFrame->Shutdown();
}

void SlendermanStaticSceneFrame::HandleEvent(GlEngine::Events::Event &evt)
{
    if (!evt.IsHandled() && renderedFrame != nullptr)
    {
        renderedFrame->HandleEvent(evt);
    }
}
