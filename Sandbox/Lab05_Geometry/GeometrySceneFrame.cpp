#include "stdafx.h"
#include "GeometrySceneFrame.h"

#include "../CameraTargetObject.h"
#include "CameraGameObject.h"
#include "Lab5Controls.h"
#include "AmbientLightSource.h"
#include "../LightSourceObject.h"
#include "../RawGraphicsObject.h"
#include "../TemplateObj.h"

#include "PointVolume.h"

extern std::string billboardVertex;
extern std::string billboardGeometry;
extern std::string billboardFragment;

extern std::string wireframeVertex;
extern std::string wireframeGeometry;
extern std::string wireframeFragment;

extern std::string hairVertex;
extern std::string hairGeometry;
extern std::string hairFragment;

static GlEngine::ShaderFactory::Property<float> prop_WireframeThickness("wireframe_thickness");

GeometrySceneFrame::GeometrySceneFrame()
{
    props = {
        { 0, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix },
        { 3, &GlEngine::ShaderFactory::prop_ScreenDimensions },
        { 4, &prop_WireframeThickness }
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

    auto ambient = new GlEngine::AmbientLightSource({ .25f, .25f, .25f });
    auto pointLight = CreateGameObject<PointLightSourceObject>();
    controls->SetControllingLight(pointLight->lightSource());
    pointLight->lightSource()->SetPosition({ 0, 2.5, -2.5 });

    ambient;

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

            return (GlEngine::GraphicsObject*)gobj; // why do I need this?
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
