#include "stdafx.h"
#include "LightsAndEffectsSceneFrame.h"

#include "CameraComponent.h"
#include "Lab3ControlsComponent.h"
#include "../CameraTargetComponent.h"

#include "Tree.h"
#include "RandomUtils.h"
#include "../LightSourceObject.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "StageGraphicsObject.h"
#include "PointLightSource.h"
#include "AmbientLightSource.h"
#include "FogSource.h"

#include "Property.h"
#include "Attribute.h"
#include "ShaderFactory.h"
#include "SpotlightSource.h"
#include "Environment.h"

#include "../RawGraphicsObject.h"

#include "ObjGraphicsObject.h"
#include "PhongFogMaterial.h"
#include "MultiPhongMaterial.h"
#include "PlaneGraphicsObject.h"
#include "../OrbitingLight.h"

#include "LogUtils.h"

typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;
typedef GlEngine::PointLightSource PointLightSource;
typedef GlEngine::SpotlightSource SpotlightSource;

LightsAndEffectsSceneFrame::LightsAndEffectsSceneFrame()
    : spotLightSource(nullptr), totalDelta(0)
{
}
LightsAndEffectsSceneFrame::~LightsAndEffectsSceneFrame()
{
    SafeDelete(spotLightSource);
}

bool LightsAndEffectsSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    GlEngine::CameraComponent* cameraComponent;
    CreateDefaultPipeline(cameraComponent);
    auto cameraTarget = new CameraTargetComponent();
    cameraComponent->gameObject()->AddComponent(cameraTarget);
    cameraComponent->gameObject()->localTransform()->SetPosition({ 0, 3.5, 7 });

    auto controls = new GlEngine::GameObject(this, "Lab3ControlsComponent");
    auto controlsComponent = new Lab3ControlsComponent();
    controls->AddComponent(controlsComponent);

    auto ambient = new GlEngine::AmbientLightSource({ .1, .1, .1 });
    auto pointLight = PointLightSourceObject::Create(this, "PointLight1");
    auto lightSource = pointLight->component<PointLightSourceObject>()->lightSource();
    controlsComponent->SetControllingLight(lightSource);
    lightSource->SetPosition({ 0, 2.5, -2.5 });
    auto fog = new GlEngine::FogSource(10.f, 25.f, { 0.f, 0.f, 0.f, 1.f });

    auto treeMat = new PhongFogMaterial({ 0.f, .6f, 0.f }, { .4f, .4f, .4f }, 8);
    for (int q = -2; q <= 2; q++)
    {
        for (int w = -2; w <= 2; w++)
        {
            float rndX = GlEngine::Util::random(2.f) - 1,
                  rndZ = GlEngine::Util::random(2.f) - 1;
            auto tree = new GlEngine::GameObject(this, "Tree");
            auto treeGfx = GlEngine::ObjGraphicsObject::Create("Tree_Gfx", "Resources/tree.obj", treeMat, { ambient, lightSource, fog });
            tree->AddComponent(treeGfx);
            tree->localTransform()->SetPosition({ (q * 5) + rndX, 0, (w * 5) + rndZ });
        }
    }

    auto grassTex = GlEngine::Texture::FromFile("Textures/grass0.png"s);
    auto plane1 = new GlEngine::GameObject(this, "NormalMapPlane");
    auto planeMat = new PhongFogMaterial(grassTex);
    auto planeGfx1 = new GlEngine::PlaneGraphicsObject("Plane1_Gfx", planeMat, { 40, 40 }, { 20, 20 });
    planeGfx1->AddPropertyProvider(ambient);
    planeGfx1->AddPropertyProvider(lightSource);
    planeGfx1->AddPropertyProvider(fog);
    plane1->AddComponent(planeGfx1);
    plane1->localTransform()->SetPosition({ 0, 0, 0 });

    struct {
        Vector<3> rotationAxis = { 1, 0, 0 };
        float totalDelta = 0.0;
        float rotationSpeed = 0.5;
        float distance = 3.0;
        LightSourceObject<PointLightSource>* lightSource = nullptr;
    } celData;

    auto celMat = TemplateMaterial::Factory()
        ->Attribute(&GlEngine::ShaderFactory::attr_GlPosition)
        ->Attribute(&GlEngine::ShaderFactory::attr_AmbientDiffuse)
        ->Attribute(&GlEngine::ShaderFactory::attr_RgbBaseColor)
        ->Attribute(&GlEngine::ShaderFactory::attr_CelShading)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_RgbColor, Vector<3> { 1.0f, 0.2f, 1.0f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, Vector<3> { 0.9f, 0.9f, 0.9f })
        ->Provide(&GlEngine::ShaderFactory::prop_CelLevels, Lab3ControlsComponent::celShadingSteps)
        ->Create();
    auto lightSource1 = PointLightSourceObject::Create(this, "LightSource1");
    auto pointLight1 = lightSource1->component<PointLightSourceObject>()->lightSource();
    auto torus1 = OrbitingLight::Create(this, "CelTorus", celMat, "Resources/torus.obj", pointLight1, { 0, 0, 1 }, { ambient });
    torus1->localTransform()->SetPosition({ 15, 5, 0 });

    //struct {
    //    LightSourceObject<PointLightSource> *rotXLight = nullptr,
    //                                        *rotYLight = nullptr,
    //                                        *rotZLight = nullptr;
    //    float rotXDelta = 0,
    //          rotYDelta = 0,
    //          rotZDelta = 0,
    //          rotationSpeed = .5f,
    //          distance = 3.f;
    //} multiPhongData;
    //multiPhongData.rotXLight = CreateGameObject<LightSourceObject<PointLightSource>>();
    //multiPhongData.rotYLight = CreateGameObject<LightSourceObject<PointLightSource>>();
    //multiPhongData.rotZLight = CreateGameObject<LightSourceObject<PointLightSource>>();
    //multiPhongData.rotXLight->lightSource()->SetDiffuseColor({ 1.f, 0.f, 0.f });
    //multiPhongData.rotYLight->lightSource()->SetDiffuseColor({ 0.f, 1.f, 0.f });
    //multiPhongData.rotZLight->lightSource()->SetDiffuseColor({ 0.f, 0.f, 1.f });



    struct {
        Vector<3> floorColor = { 0.6, 0.6, 0.3 };
    } spotData;

    spotLightSource = new SpotlightSource({ 0, 1, 0 }, { 1.0, 1.0, 1.0 }, 3.0f, { 1, 0, 0 }, 10deg);
    auto spotLight = SpotlightSourceObject::Create(this, "Spotlight1", spotLightSource);
    spotLight;

    auto toriMat = TemplateMaterial::Factory()
        ->Attribute(&GlEngine::ShaderFactory::attr_GlPosition)
        ->Attribute(&GlEngine::ShaderFactory::attr_Phong)
        ->Attribute(&GlEngine::ShaderFactory::attr_RgbBaseColor)
        ->Attribute(&GlEngine::ShaderFactory::attr_Spotlight)
        ->ProvideConst(&GlEngine::ShaderFactory::prop_RgbColor, Vector<3> { 1.0f, 1.0f, 0.2f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, Vector<3> { 0.9f, 0.9f, 0.9f })
        ->ProvideConst(&GlEngine::ShaderFactory::prop_Shininess, 5.0)
        ->Create();
    for (int i = 0; i < 50; i++)
    {
        auto spotTorus = new GlEngine::GameObject(this, "SpotlightTorus");
        auto spotTorusGfx = GlEngine::ObjGraphicsObject::Create("SpotlightTorusGfx", "Resources/torus.obj", toriMat, { ambient, spotLightSource });
        spotTorus->AddComponent(spotTorusGfx);

        float rndX = GlEngine::Util::random(2.f) - 1;
        float rndY = GlEngine::Util::random(2.f) - 1;
        float rndZ = GlEngine::Util::random(2.f) - 1;
        float rotX = GlEngine::Util::random(GlEngine::Util::PI_f);
        float rotZ = GlEngine::Util::random(GlEngine::Util::PI_f);

        spotTorus->localTransform()->SetPosition({ -100 + rndX * 15, rndY * 15, rndZ * 15 });
        spotTorus->localTransform()->RotateX(rotX);
        spotTorus->localTransform()->RotateZ(rotZ);
    }

    //auto spotFloor = CreateGameObject<TemplateObj>(
    //    [](TemplateObj* self, GlEngine::GraphicsContext*) -> GlEngine::GraphicsObject*
    //    {
    //        auto gobj = new StageGraphicsObject(false);
    //        for (auto it = self->providers().begin(); it != self->providers().end(); it++)
    //            gobj->AddPropertyProvider(*it);
    //        gobj->SetMaterial(&self->material());
    //        return gobj;
    //    },
    //    TemplateMaterial::Factory()
    //        ->Provide(&GlEngine::ShaderFactory::prop_RgbColor, spotData.floorColor)
    //        ->Provide(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, spotData.reflectionCoef)
    //        ->Provide(&GlEngine::ShaderFactory::prop_AmbientLightColor, spotData.ambient)
    //        ->Provide(&GlEngine::ShaderFactory::prop_Shininess, spotData.shininess)
    //        ->Create(),
    //    std::vector<IPropertyProvider*> {
    //        spotData.lightSource->lightSource()
    //    },
    //    [spotData](TemplateObj*, float delta) mutable {
    //        spotData.lightSource->lightSource()->SetAngleAttenuation(Lab3Controls::spotlightAttenuation);
    //        spotData.lightSource->lightSource()->SetCutoffTheta(Lab3Controls::spotlightCutoffAngle);

    //    }
    //);
    //spotFloor->SetPosition({ -100, -10, 0 });

    return true;
}

static const float rotationSpeed = .5f;

void LightsAndEffectsSceneFrame::Tick(float delta)
{
    Frame::Tick(delta);

    if (spotLightSource != nullptr)
    {
        spotLightSource->SetAngleAttenuation(Lab3ControlsComponent::spotlightAttenuation);
        spotLightSource->SetCutoffTheta(Lab3ControlsComponent::spotlightCutoffAngle);

        if (LabControlsComponent::isPaused) return;
        else if (!LabControlsComponent::rotateY) return;

        totalDelta += delta;
        auto rotationAmount = totalDelta * rotationSpeed;
        auto transformMatrix = Matrix<4, 4>::TranslateMatrix({ 0, 0, 1 }) * Matrix<4, 4>::YawMatrix(rotationAmount) * Matrix<4, 4>::TranslateMatrix({ -120, 0, -15 });
        auto transformedPosition = transformMatrix.Transpose() * Vector<4>{ 0, 0, 0, 1 };
        Vector<3> tPos = { transformedPosition[0], transformedPosition[1], transformedPosition[2] };
        auto relPosition = Vector<3> { -120, 0, -15 } - tPos;
        auto direction = Vector<3>{ relPosition[0], relPosition[1], relPosition[2] }.Normalized();

        spotLightSource->SetPosition({ transformedPosition[0], transformedPosition[1], transformedPosition[2] });
        spotLightSource->SetDirection(direction);
    }
}
