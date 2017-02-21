#include "stdafx.h"
#include "OrbitingLight.h"
#include "ObjGraphicsObject.h"
#include "DiffuseMaterial.h"
#include "RandomUtils.h"
#include "MatrixStack.h"
#include "AmbientLightSource.h"
#include "PointLightSource.h"
#include "LabControlsComponent.h"

GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, float distance, float rotationSpeed)
{
    return Create(frame, name, color, reflectionCoef, "Resources/torus.obj", lightSource, randomRotateAxis(), distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance, float rotationSpeed)
{
    auto mat = new GlEngine::DiffuseMaterial(color, reflectionCoef);
    return Create(frame, name, mat, "Resources/torus.obj", lightSource, rotationAxis, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, std::string modelPath, GlEngine::PointLightSource *lightSource, float distance, float rotationSpeed)
{
    return Create(frame, name, color, reflectionCoef, modelPath, lightSource, randomRotateAxis(), distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, std::string modelPath, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance, float rotationSpeed)
{
    auto mat = new GlEngine::DiffuseMaterial(color, reflectionCoef);
    return Create(frame, name, mat, modelPath, lightSource, rotationAxis, distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, GlEngine::PointLightSource *lightSource, float distance, float rotationSpeed)
{
    return Create(frame, name, mat, "Resources/torus.obj", lightSource, randomRotateAxis(), distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance, float rotationSpeed)
{
    return Create(frame, name, mat, "Resources/torus.obj", lightSource, randomRotateAxis(), distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, std::string modelPath, GlEngine::PointLightSource *lightSource, float distance, float rotationSpeed)
{
    return Create(frame, name, mat, lightSource, randomRotateAxis(), distance, rotationSpeed);
}
GlEngine::GameObject *OrbitingLight::Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, std::string modelPath, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance, float rotationSpeed)
{
    assert(mat != nullptr);
    assert(lightSource != nullptr);
    auto gobj = new GlEngine::GameObject(frame, name);
    auto objObj = GlEngine::ObjGraphicsObject::Create(name, modelPath.c_str(), mat, { lightSource });
    gobj->AddComponent(objObj);
    gobj->AddComponent(new OrbitingLight(lightSource, rotationAxis, distance, rotationSpeed));
    return gobj;
}

OrbitingLight::OrbitingLight(GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance, float rotationSpeed)
    : GameComponent("OrbitingLight"), _lightSource(lightSource), rotationAxis(rotationAxis), distance(distance), rotationSpeed(rotationSpeed), totalDelta(0)
{
}
OrbitingLight::~OrbitingLight()
{
}

bool OrbitingLight::InitializeAsync()
{
    gameObject()->transform.Rotate(GlEngine::Util::random(3.14159f * 2), randomRotateAxis());
    return GlEngine::GameComponent::InitializeAsync();
}

void OrbitingLight::Tick(float delta)
{
    if (LabControlsComponent::isPaused) return;
    else if (!!rotationAxis[0] && !LabControlsComponent::rotateZ) return;
    else if (!!rotationAxis[1] && !LabControlsComponent::rotateY) return;
    else if (!!rotationAxis[2] && !LabControlsComponent::rotateX) return;

    totalDelta += delta;
    auto rotationAmount = totalDelta * rotationSpeed;
    auto position = gameObject()->transform.position;
    auto transformMatrix = !!rotationAxis[0] ? Matrix<4, 4>::TranslateMatrix({ 0, distance, 0 }) * Matrix<4, 4>::RollMatrix(rotationAmount)  * Matrix<4, 4>::TranslateMatrix(position) :
                           !!rotationAxis[1] ? Matrix<4, 4>::TranslateMatrix({ 0, 0, distance }) * Matrix<4, 4>::YawMatrix(rotationAmount)   * Matrix<4, 4>::TranslateMatrix(position) :
                                               Matrix<4, 4>::TranslateMatrix({ distance, 0, 0 }) * Matrix<4, 4>::PitchMatrix(rotationAmount) * Matrix<4, 4>::TranslateMatrix(position);
    auto transformedPosition = transformMatrix.Transpose() * Vector<4>{ 0, 0, 0, 1 };
    _lightSource->SetPosition({ transformedPosition[0], transformedPosition[1], transformedPosition[2] });
}

static float randomVecComponent()
{
    return GlEngine::Util::random(2.f) - 1;
}
Vector<3> OrbitingLight::randomRotateAxis()
{
    while (true)
    {
        Vector<3> axis = { randomVecComponent(), randomVecComponent(), randomVecComponent() };
        if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0) continue;
        if (sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]) > 1) continue;
        return axis;
    }
}
