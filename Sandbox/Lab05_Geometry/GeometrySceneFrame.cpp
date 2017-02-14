#include "stdafx.h"
#include "GeometrySceneFrame.h"

#include "PointVolume.h"

#include "../CameraTargetObject.h"
#include "CameraGameObject.h"
#include "Lab5Controls.h"
#include "AmbientLightSource.h"
#include "../LightSourceObject.h"
#include "../RawGraphicsObject.h"
#include "../TemplateObj.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "RandomUtils.h"
#include "Texture.h"

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
    props = {
        { 0, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix },
        { 3, &GlEngine::ShaderFactory::prop_ScreenDimensions },
        { 4, &prop_WireframeThickness },
        { 5, &prop_BillboardTexture },
        { 6, &prop_BillboardSize },
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

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    this->CreateGameObject<CameraTargetObject>(cameraObject);

    CreateGameObject<Lab5Controls>();

    auto pointVboFactory = PointVolume<float, float>::Generate({ -1, -1, -1 }, { 1, 1, 1 }, 20 * 20 * 20, &prop_BillboardTimeOffset, &prop_BillboardSpeed, [](Vector<3> pos)
    {
        //Generate random billboard time offset and billboard speed for each snowflake
        return std::tuple<float, float>(GlEngine::Util::random(2000.f), .4f + GlEngine::Util::random(1.6f));
    });
    CreateGameObject<TemplateObj>(
        [this, pointVboFactory](TemplateObj *self, GlEngine::GraphicsContext*)
        {
            auto gobj = new RawGraphicsObject(
                pointVboFactory,
                &this->billboardSource,
                &this->props
            );
            for (size_t q = 0; q < self->providers().size(); q++)
                gobj->AddPropertyProvider(self->providers()[q]);
            gobj->SetMaterial(&self->material());

            return gobj;
        },
        TemplateMaterial::Factory()
            ->Name("BillboardMaterial")
            ->Provide(&prop_BillboardTexture, snowTex)
            ->Provide(&prop_BillboardSize, snowflakeSize)
            ->Create()
    );

    auto wireframeTeapot = CreateGameObject<TemplateObj>(
        [this](TemplateObj* self, GlEngine::GraphicsContext*) {
            auto gobj = new RawGraphicsObject(
                "Resources/teapot.obj",
                &this->wireframeSource,
                &this->props
            );
            for (size_t q = 0; q < self->providers().size(); q++)
                gobj->AddPropertyProvider(self->providers()[q]);
            gobj->SetMaterial(&self->material());

            return gobj;
        },
        TemplateMaterial::Factory()
            ->Name("WireframeMaterial")
            ->Provide(&prop_WireframeThickness, Lab5Controls::wireframeThickness)
            ->Create()
    );
    wireframeTeapot->SetPosition({ -8, 0, 0 });

    auto hairyTorus = CreateGameObject<TemplateObj>(
        [this](TemplateObj* self, GlEngine::GraphicsContext*) {
            auto gobj = new RawGraphicsObject(
                "Resources/teapot.obj",
                &this->hairSource,
                &this->props
            );
            for (size_t q = 0; q < self->providers().size(); q++)
                gobj->AddPropertyProvider(self->providers()[q]);
            gobj->SetMaterial(&self->material());

            return gobj;
        }
    );
    hairyTorus->SetPosition({ 0, 0, 0 });

    auto explodeTeapot = CreateGameObject<TemplateObj>(
        [this](TemplateObj* self, GlEngine::GraphicsContext*) {
            auto gobj = new RawGraphicsObject(
                "Resources/teapot.obj",
                &this->explodeSource,
                &this->props
            );
            for (size_t q = 0; q < self->providers().size(); q++)
                gobj->AddPropertyProvider(self->providers()[q]);
            gobj->SetMaterial(&self->material());

            return gobj;
        }
    );
    explodeTeapot->SetPosition({ 8, 0, 0 });

    return true;
}
