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
#include "Environment.h"

#include "Texture.h"

extern std::string billboardVertex;
extern std::string billboardGeometry;
extern std::string billboardFragment;
static GlEngine::ShaderFactory::Property<GlEngine::Texture*> prop_BillboardTexture("billboard_texture");

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
        { 0, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix },
        { 3, &GlEngine::ShaderFactory::prop_ScreenDimensions },
        { 4, &prop_WireframeThickness },
        { 5, &prop_BillboardTexture },
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

    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    CreateGameObject<Lab5Controls>();

    auto pointVboFactory = PointVolume<>::Generate({ -3, -3, -3 }, { 3, 3, 3 }, 20);
    auto billboardSnow = CreateGameObject<TemplateObj>(
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
            ->Create()
    );
    billboardSnow->SetPosition({ -8, 0, 0 });

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
    wireframeTeapot->SetPosition({ 0, 0, 0 });

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
    hairyTorus->SetPosition({ 8, 0, 0 });

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
    explodeTeapot->SetPosition({ 16, 0, 0 });

    return true;
}
