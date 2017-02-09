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

GeometrySceneFrame::GeometrySceneFrame()
{
    props = {
        { 0, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix },
        { 3, &GlEngine::ShaderFactory::prop_ScreenDimensions },
        { 4, &prop_WireframeThickness },
        { 5, &prop_BillboardTexture }
    };

    billboardSource = {
        &billboardVertex,
        nullptr,
        nullptr,
        &billboardGeometry,
        &billboardFragment,
    };
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
}
GeometrySceneFrame::~GeometrySceneFrame()
{
}

bool GeometrySceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    auto controls = CreateGameObject<Lab5Controls>();

    auto snowTex = GlEngine::Texture::FromFile("Textures/snowflake.png", GlEngine::TextureFlag::Translucent);
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
        new TemplateMaterial({ &prop_BillboardTexture }, {}, [snowTex](TemplateMaterial*, ShaderFactory &factory)
        {
            factory.ProvideProperty(prop_BillboardTexture, snowTex);
        })
    );
    billboardSnow->SetPosition({ -8, 0, 0 });
    snowTex; pointVboFactory; controls; billboardSnow;

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
        new TemplateMaterial({ &prop_WireframeThickness }, {}, [controls](TemplateMaterial*, ShaderFactory &factory)
        {
            factory.ProvideProperty(prop_WireframeThickness, (float)controls->wireframeThickness);
        })
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

            return (GlEngine::GraphicsObject*)gobj; // why do I need this?
        }
    );
    hairyTorus->SetPosition({ 8, 0, 0 });

    return true;
}
