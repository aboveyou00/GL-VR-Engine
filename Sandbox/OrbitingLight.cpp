#include "stdafx.h"
#include "OrbitingLight.h"
#include "ObjGraphicsObject.h"
#include "DiffuseMaterial.h"
#include "RandomUtils.h"
#include "MatrixStack.h"
#include "AmbientLightSource.h"
#include "PointLightSource.h"
#include "LabControlsComponent.h"
#include "ObjLoader.h"

static Vector<3> randomRotateAxis();

GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, ProviderList providers, float distance, float rotationSpeed)
{
    return Create(frame, name, color, reflectionCoef, "Resources/torus.obj", lightSource, randomRotateAxis(), providers, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, ProviderList providers, float distance, float rotationSpeed)
{
    auto mat = new GlEngine::DiffuseMaterial(color, reflectionCoef);
    return Create(frame, name, mat, "Resources/torus.obj", lightSource, rotationAxis, providers, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, std::string modelPath, GlEngine::PointLightSource *lightSource, ProviderList providers, float distance, float rotationSpeed)
{
    return Create(frame, name, color, reflectionCoef, modelPath, lightSource, randomRotateAxis(), providers, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, std::string modelPath, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, ProviderList providers, float distance, float rotationSpeed)
{
    auto mat = new GlEngine::DiffuseMaterial(color, reflectionCoef);
    return Create(frame, name, mat, modelPath, lightSource, rotationAxis, providers, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, GlEngine::PointLightSource *lightSource, ProviderList providers, float distance, float rotationSpeed)
{
    return Create(frame, name, mat, "Resources/torus.obj", lightSource, randomRotateAxis(), providers, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, ProviderList providers, float distance, float rotationSpeed)
{
    return Create(frame, name, mat, "Resources/torus.obj", lightSource, randomRotateAxis(), providers, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, std::string modelPath, GlEngine::PointLightSource *lightSource, ProviderList providers, float distance, float rotationSpeed)
{
    return Create(frame, name, mat, lightSource, randomRotateAxis(), providers, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, std::string modelPath, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, ProviderList providers, float distance, float rotationSpeed)
{
    assert(mat != nullptr);
    assert(lightSource != nullptr);
    auto gobj = new GlEngine::GameObject(frame, name);
    ProviderList _providers;
    for (size_t q = 0; q < providers.size(); q++)
    {
        _providers.push_back(providers[q]);
    }
    _providers.push_back(lightSource);

    auto objObj = new GlEngine::ObjLoader(modelPath.c_str(), _providers, GlEngine::ObjLoaderFlag::Graphics);
    objObj->OverrideMaterial(mat);
    gobj->AddComponent(objObj);
    
    //auto objObj = GlEngine::ObjGraphicsObject::Create(name, modelPath.c_str(), mat, _providers);
    //gobj->AddComponent(objObj);

    auto pivot = new GlEngine::GameObject(frame, "Pivot");
    pivot->SetParent(gobj);
    pivot->AddComponent(new PivotComponent(rotationAxis, rotationSpeed));

    auto lightGobj = new GlEngine::GameObject(frame, "Light");
    lightGobj->SetParent(pivot);
    lightGobj->AddComponent(new OrbitingLight(lightSource, distance, rotationAxis));
    //auto objObj2 = GlEngine::ObjGraphicsObject::Create(name, modelPath.c_str(), mat, _providers);
    //lightGobj->AddComponent(objObj2);
    //lightGobj->AddComponent(new PivotComponent(rotationAxis, rotationSpeed));

    return gobj;
}

OrbitingLight::OrbitingLight(GlEngine::PointLightSource *lightSource, float distance, Vector<3> rotationAxis)
    : GameComponent("OrbitingLight"), _lightSource(lightSource), distance(distance), rotationAxis(rotationAxis)
{
}
OrbitingLight::~OrbitingLight()
{
}

bool OrbitingLight::InitializeAsync()
{
    Vector<3> raxis = !!rotationAxis[0] ? Vector<3> { 1, 0, 0 } :
                      !!rotationAxis[1] ? Vector<3> { 0, 1, 0 } :
                                          Vector<3> { 0, 0, 1 };
    gameObject()->localTransform()->SetPosition(raxis * distance);
    return GlEngine::GameComponent::InitializeAsync();
}

void OrbitingLight::Tick(float)
{
    this->_lightSource->SetPosition(this->gameObject()->globalTransform()->position());
}

PivotComponent::PivotComponent(Vector<3> rotationAxis, float rotationSpeed)
    : GameComponent("OrbitingLight"), rotationAxis(rotationAxis), rotationSpeed(rotationSpeed), totalDelta(0)
{
}
PivotComponent::~PivotComponent()
{
}

void PivotComponent::Tick(float delta)
{
    if (LabControlsComponent::isPaused) return;
    else if (!!rotationAxis[0] && !LabControlsComponent::rotateZ) return;
    else if (!!rotationAxis[1] && !LabControlsComponent::rotateY) return;
    else if (!!rotationAxis[2] && !LabControlsComponent::rotateX) return;

    Vector<3> raxis = !!rotationAxis[0] ? Vector<3> { 0, 1, 0 } :
                      !!rotationAxis[1] ? Vector<3> { 0, 0, 1 } :
                                          Vector<3> { 1, 0, 0 };
    totalDelta += delta;
    this->gameObject()->localTransform()->SetOrientation(Quaternion<>(this->rotationSpeed * this->totalDelta, raxis));
}

static float randomVecComponent()
{
    return GlEngine::Util::random(2.f) - 1;
}
static Vector<3> randomRotateAxis()
{
    while (true)
    {
        Vector<3> axis = { randomVecComponent(), randomVecComponent(), randomVecComponent() };
        if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0) continue;
        if (sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]) > 1) continue;
        return axis;
    }
}
