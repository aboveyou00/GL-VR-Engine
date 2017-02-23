#include "stdafx.h"
#include "GeometrySceneFrame.h"

#include "PointVolume.h"

#include "CameraComponent.h"
#include "../CameraTargetComponent.h"
#include "Lab5ControlsComponent.h"
#include "AmbientLightSource.h"
#include "../LightSourceObject.h"
#include "../RawGraphicsObject.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "RandomUtils.h"
#include "Texture.h"
#include "CubeGraphicsObject.h"

//HACK HACK HACK
#include "../Sandbox.h"
#include "RenderTarget.h"

extern std::string billboardVertex;
extern std::string billboardGeometry;
extern std::string billboardFragment;
static GlEngine::ShaderFactory::Property<GlEngine::Texture*> prop_BillboardTexture("billboard_texture");
static GlEngine::ShaderFactory::Property<Vector<2>> prop_BillboardSize("billboard_size");
static GlEngine::ShaderFactory::Property<float> prop_BillboardTimeOffset("billboard_time_offset");
static GlEngine::ShaderFactory::Property<float> prop_BillboardSpeed("billboard_speed");

extern std::string wireframeVertex;
extern std::string wireframeGeometry;
extern std::string wireframeFragment;
static GlEngine::ShaderFactory::Property<float> prop_WireframeThickness("wireframe_thickness");

extern std::string hairVertex;
extern std::string hairGeometry;
extern std::string hairFragment;

extern std::string hairLineVertex;
extern std::string hairLineGeometry;
extern std::string hairLineGeometryPassthrough;
extern std::string hairLineFragment;

extern std::string explodeVertex;
extern std::string explodeGeometry;
extern std::string explodeFragment;

GeometrySceneFrame::GeometrySceneFrame()
{
    billboardProps = {
        { 0, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix },
        { 3, &GlEngine::ShaderFactory::prop_ScreenDimensions },
        { 5, &prop_BillboardTexture },
        { 6, &prop_BillboardSize },
        { 7, &GlEngine::ShaderFactory::prop_GameTime }
    };
    wireframeProps = {
        { 0, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix },
        { 3, &GlEngine::ShaderFactory::prop_ScreenDimensions },
        { 4, &prop_WireframeThickness }
    };
    hairProps = {
        { 0, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix }
    };
    explodeProps = {
        { 0, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix },
        { 7, &GlEngine::ShaderFactory::prop_GameTime }
    };

    billboardSource = {
        &billboardVertex,
        nullptr,
        nullptr,
        &billboardGeometry,
        &billboardFragment,
    };
    snowTex = GlEngine::Texture::FromFile("Textures/snowflake.png", GlEngine::TextureFlag::Translucent);
    snowflakeSize = { 32, 32 };

    wireframeSource = {
        &wireframeVertex,
        nullptr,
        nullptr,
        &wireframeGeometry,
        &wireframeFragment,
    };
    hairSource = {
        &hairVertex,
        nullptr,
        nullptr,
        &hairGeometry,
        &hairFragment,
    };
    explodeSource = {
        &explodeVertex,
        nullptr,
        nullptr,
        &explodeGeometry,
        &explodeFragment
    };
}
GeometrySceneFrame::~GeometrySceneFrame()
{
    snowTex = nullptr; //This will be deleted by the resource loader thread
}

bool GeometrySceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    auto cameraTarget = CameraTargetComponent::Create(this, "CameraTarget");

    auto cameraObject = GlEngine::CameraComponent::Create(this, "Camera");
    cameraObject->transform.position = { 0, -3.5, 7 };

    auto cameraComponent = cameraObject->component<GlEngine::CameraComponent>();
    cameraComponent->SetTargetObject(cameraTarget);
    cameraComponent->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraComponent->SetClearColor({ .4, .4, .4 });
    Sandbox::windowRenderTarget->SetCamera(cameraComponent);

    auto controls = new GlEngine::GameObject(this, "Lab5ControlsComponent");
    auto controlsComponent = new Lab5ControlsComponent();
    controls->AddComponent(controlsComponent);

    auto pointVboFactory = PointVolume<float, float>::Generate({ -1, -1, -1 }, { 1, 1, 1 }, 20 * 20 * 20, &prop_BillboardTimeOffset, &prop_BillboardSpeed, [](Vector<3> pos)
    {
        //Generate random billboard time offset and billboard speed for each snowflake
        return std::tuple<float, float>(GlEngine::Util::random(2000.f), .4f + GlEngine::Util::random(1.6f));
    });
    auto snowGfx = new RawGraphicsObject(
        "SnowGfx",
        pointVboFactory,
        &this->billboardSource,
        &this->billboardProps
    );
    snowGfx->SetMaterial(TemplateMaterial::Factory()
        ->Name("BillboardMaterial")
        ->Provide(&prop_BillboardTexture, snowTex)
        ->Provide(&prop_BillboardSize, snowflakeSize)
        ->Create()
    );
    auto snowObj = new GlEngine::GameObject(this, "Snow");
    snowObj->AddComponent(snowGfx);
    
    auto wireframeGfx = new RawGraphicsObject(
        "WireframeGfx",
        "Resources/teapot.obj",
        &this->wireframeSource,
        &this->wireframeProps
    );
    wireframeGfx->SetMaterial(TemplateMaterial::Factory()
        ->Name("WireframeMaterial")
        ->Provide(&prop_WireframeThickness, Lab5ControlsComponent::wireframeThickness)
        ->Create()
    );
    auto wireframeTeapot = new GlEngine::GameObject(this, "WireframeTeapot");
    wireframeTeapot->AddComponent(wireframeGfx);
    wireframeTeapot->transform.SetPosition({ -8, 0, 0 });

    auto hairGfx = new RawGraphicsObject(
        "HairGfx",
        "Resources/teapot.obj",
        &this->hairSource,
        &this->hairProps
    );
    hairGfx->SetMaterial(TemplateMaterial::Factory()->Create());
    auto hairyTeapot = new GlEngine::GameObject(this, "HairTeapot");
    hairyTeapot->AddComponent(hairGfx);

    auto explodeGfx = new RawGraphicsObject(
        "ExplodeGfx",
        "Resources/teapot.obj",
        &this->explodeSource,
        &this->explodeProps
    );
    explodeGfx->SetMaterial(TemplateMaterial::Factory()->Create());
    auto explodeTeapot = new GlEngine::GameObject(this, "ExplodeTeapot");
    explodeTeapot->AddComponent(explodeGfx);
    explodeTeapot->transform.SetPosition({ 8, 0, 0 });

    return true;
}
