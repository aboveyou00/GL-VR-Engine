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

#include "Color.h"

#include <map>
#include "Property.h"
#include "ComponentArray.h"
using namespace GlEngine::ShaderFactory;
extern Property<float> prop_StartTime, prop_LiveTime;
extern Property<Vector<3>> prop_StartPosition, prop_StartVelocity, prop_Acceleration;
extern std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> fountainProps;
extern ShaderSource fountainSource;

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

    auto cameraTarget = CameraTargetComponent::Create(this, "CameraTarget");

    auto cameraObject = GlEngine::CameraComponent::Create(this, "Camera");
    cameraObject->transform.position = { 0, -3.5, 7 };

    auto cameraComponent = CreateDefaultCamera();
    cameraComponent->SetTargetObject(cameraTarget);
    cameraComponent->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    //cameraComponent->SetClearColor({ .4, .4, .4 });

    auto controls = new GlEngine::GameObject(this, "Lab5ControlsComponent");
    auto controlsComponent = new LabControlsComponent();
    controls->AddComponent(controlsComponent);

    auto pointVboFactory = PointVolume<float, float, Vector<3>, Vector<3>, Vector<3>>::Generate(10000, &prop_StartTime, &prop_LiveTime, &prop_RgbColor, &prop_StartVelocity, &prop_Acceleration, [](unsigned idx)
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
            idx / 60.f / 30,
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
    fountainObj->transform.position = { 0, -5, -15 };





    return true;
}
