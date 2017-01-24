#include "stdafx.h"
#include "LightsAndEffectsSceneFrame.h"
#include "Tree.h"

#include "CameraGameObject.h"
#include "Lab3Controls.h"
#include "../CameraTargetObject.h"

#include "RandomUtils.h"
#include "../LightSourceObject.h"
#include "../TemplateTorus.h"
#include "PointLightSource.h"
#include "AmbientLightSource.h"
#include "FogSource.h"

#include "Property.h"
#include "Attribute.h"
#include "ShaderFactory.h"

typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;

LightsAndEffectsSceneFrame::LightsAndEffectsSceneFrame()
{
}
LightsAndEffectsSceneFrame::~LightsAndEffectsSceneFrame()
{
}

bool LightsAndEffectsSceneFrame::Initialize()
{
    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    auto controls = CreateGameObject<Lab3Controls>();

    auto ambientLightSource = new GlEngine::AmbientLightSource({ .1f, .1f, .1f });
    auto lightGobj = CreateGameObject<LightSourceObject>();
    auto fog = new GlEngine::FogSource(0, 15.f, { 0.f, 0.f, 0.f, 1.f });
    lightGobj->lightSource()->SetPosition({ 0, 6.f, -6.f });

    for (int q = -2; q <= 2; q++)
    {
        for (int w = -2; w <= 2; w++)
        {
            float rndX = GlEngine::Util::random(2.f) - 1,
                  rndZ = GlEngine::Util::random(2.f) - 1;
            CreateGameObject<Tree>(Vector<3> { (q * 5) + rndX, 0, (w * 5) + rndZ }, std::vector<IPropertyProvider*> { ambientLightSource, lightGobj->lightSource(), fog });
        }
    }

    auto color = Vector<3>{ 1.0, 1.0, 0.0 };
    auto reflectionCoef = Vector<3>{ .9f, .9f, .9f };

    auto lightSource6 = CreateGameObject<LightSourceObject>();
    auto cel = CreateGameObject<TemplateTorus>(
        new TemplateMaterial(
    {
        &GlEngine::ShaderFactory::prop_RgbColor,
        &GlEngine::ShaderFactory::prop_ReflectionCoefficient,
        &GlEngine::ShaderFactory::prop_CelLevels
    },
    {
        &GlEngine::ShaderFactory::attr_GlPosition,
        &GlEngine::ShaderFactory::attr_DiffuseOnly,
        &GlEngine::ShaderFactory::attr_RgbBaseColor,
        &GlEngine::ShaderFactory::attr_CelShading
    },
            [color, reflectionCoef, controls](GlEngine::ShaderFactory::ShaderFactory& factory)
    {
        factory.ProvideProperty(GlEngine::ShaderFactory::prop_RgbColor, color);
        factory.ProvideProperty(GlEngine::ShaderFactory::prop_ReflectionCoefficient, reflectionCoef);
        factory.ProvideProperty(GlEngine::ShaderFactory::prop_CelLevels, (int)controls->celShadingSteps);
    }
        ), color, reflectionCoef, lightSource6->lightSource(), Vector<3> {1, 0, 0}
    );
    cel->SetPosition({ 0, 10, 0 });

    return true;
}
