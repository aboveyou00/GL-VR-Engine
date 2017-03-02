#include "stdafx.h"
#include "ParticlesSceneFrame.h"

#include "../CameraTargetComponent.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "../LabControlsComponent.h"

#include "../PointVolume.h"
#include "RawShaderFactory.h"
#include "../RawGraphicsObject.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "MathUtils.h"
#include "RenderPipeline.h"

#include "AmbientLightSource.h"
#include "../LightSourceObject.h"
#include "PhongMaterial.h"
#include "ObjGraphicsObject.h"
#include "InstancedGraphicsObject.h"
#include "Property.h"

#include "Color.h"

#include <map>
#include "Property.h"
#include "ComponentArray.h"

using namespace GlEngine::ShaderFactory;

extern Property<float> prop_StartTime, prop_LiveTime;
extern Property<Vector<3>> prop_StartPosition, prop_StartVelocity, prop_Acceleration;
extern std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> fountainProps;
extern ShaderSource fountainSource;

extern std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> instancedPhongProps;
extern ShaderSource instancedPhongSource;

const float MAX_THETA = 30deg;

ParticlesSceneFrame::ParticlesSceneFrame()
{
    particleTex = GlEngine::Texture::FromFile("Textures/particle.png", GlEngine::TextureFlag::Translucent);
}
ParticlesSceneFrame::~ParticlesSceneFrame()
{
}

bool ParticlesSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    GlEngine::CameraComponent* cameraComponent;
    auto pipeline = CreateDefaultPipeline(cameraComponent);
    pipeline->SetClearColor({ .4, .4, .4 });

    cameraComponent->gameObject()->localTransform()->SetPosition({ 0, 3.5, 7 });
    
    auto cameraTarget = new CameraTargetComponent();
    cameraComponent->gameObject()->AddComponent(cameraTarget);

    auto controls = new GlEngine::GameObject(this, "Lab5ControlsComponent");
    auto controlsComponent = new LabControlsComponent();
    controls->AddComponent(controlsComponent);

    const unsigned TOTAL_PARTICLES = 10000;
    const float PARTICLES_PER_FRAME = 30.f;
    //const unsigned TOTAL_PARTICLES = 1000000;
    //const float PARTICLES_PER_FRAME = 10000.f;

    auto pointVboFactory = PointVolume<float, float, Vector<3>, Vector<3>, Vector<3>>::Generate(TOTAL_PARTICLES, &prop_StartTime, &prop_LiveTime, &prop_RgbColor, &prop_StartVelocity, &prop_Acceleration, [PARTICLES_PER_FRAME](unsigned idx)
    {
        float theta = GlEngine::Util::random(MAX_THETA * 2) - MAX_THETA;
        float phi = GlEngine::Util::random(2 * GlEngine::Util::PI_f);
        Vector<3> v = {
            sin(theta) * cos(phi),
            cos(theta),
            sin(theta) * sin(phi)
        };

        float M = 3.f + GlEngine::Util::random(1.5f);

        //Generate random billboard time offset and billboard speed for each snowflake
        return std::tuple<float, float, Vector<3>, Vector<3>, Vector<3>>(
            idx / 60.f / PARTICLES_PER_FRAME,
            3.f + GlEngine::Util::random(2.f),
            GlEngine::HsvToRgb(GlEngine::Util::random(1.f), 1.f, 1.f),
            v * M,
            { GlEngine::Util::random(2.f) - 1, GlEngine::Util::random(2.f) - 1, GlEngine::Util::random(2.f) - 1 }
        );
    });
    auto fountainGfx = new RawGraphicsObject(
        "FountainGfx",
        pointVboFactory,
        &fountainSource,
        &fountainProps
    );
    fountainGfx->SetMaterial(TemplateMaterial::Factory()
        ->Name("ParticleMaterial")
        ->ProvideConst(&prop_StartPosition, Vector<3> { 0, 0, 0 })
        ->Provide(&prop_Texture, particleTex)
        ->ProvideConst(&prop_BillboardSize, Vector<2> { 32, 32 })
        ->Create()
    );
    auto fountainObj = new GlEngine::GameObject(this, "ParticleFountain");
    fountainObj->AddComponent(fountainGfx);
    fountainObj->localTransform()->SetPosition({ 0, -5, -15 });

    auto ambient = new GlEngine::AmbientLightSource({ .1, .1, .1 });
    auto pointLight = PointLightSourceObject::Create(this, "PointLight1");
    auto lightSource = pointLight->component<PointLightSourceObject>()->lightSource();
    controlsComponent->SetControllingLight(lightSource);
    lightSource->SetPosition({ 0, 2.5, -2.5 });

    auto singleAsteroid = new RawGraphicsObject("AsteroidGfx", "Resources/asteroid.obj", &instancedPhongSource, &instancedPhongProps);
    singleAsteroid->AddPropertyProvider(ambient);
    singleAsteroid->AddPropertyProvider(lightSource);
    singleAsteroid->SetMaterial(TemplateMaterial::Factory()
        ->Attribute(&attr_RgbBaseColor)
        ->Attribute(&attr_GlPosition)
        ->Attribute(&attr_Phong)
        ->ProvideConst(&prop_RgbColor, Vector<3> { .6, .6, 1 })
        ->ProvideConst(&prop_ReflectionCoefficient, Vector<3> { .8, .8, .8 })
        ->ProvideConst(&prop_Shininess, 20)
        ->Create()
    );
    auto instancedAsteroids = new GlEngine::InstancedGraphicsObject<GlEngine::VboType::Float, Matrix<4, 4>>("InstancedAsteroids", singleAsteroid, &GlEngine::ShaderFactory::prop_InstanceModelMatrix);
    auto asteroids = new GlEngine::GameObject(this, "Asteroids");
    asteroids->AddComponent(instancedAsteroids);
    asteroids->localTransform()->Translate({ 5, 0, -5 });

    for (size_t q = 0; q < 10; q++)
    {
        for (size_t w = 0; w < 10; w++)
        {
            for (size_t e = 0; e < 10; e++)
            {
                auto axis = Vector<3> { GlEngine::Util::random(2.f) - 1.f, GlEngine::Util::random(2.f) - 1.f, GlEngine::Util::random(2.f) - 1.f }.Normalized(1);
                auto rot = Quaternion<>(GlEngine::Util::random(180deg), axis);
                instancedAsteroids->AddInstance(rot.ToMatrix() * Matrix<4, 4>::TranslateMatrix(Vector<3> { q, w, e } * 3));
            }
        }
    }
    instancedAsteroids->Finalize();

    return true;
}
