#include "stdafx.h"
#include "LitTorus.h"
#include "ObjGraphicsObject.h"
#include "DiffuseMaterial.h"
#include "RandomUtils.h"
#include "MatrixStack.h"
#include "AmbientLightSource.h"
#include "PointLightSource.h"
#include "../LabControls.h"

LitTorus::LitTorus(Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, float distance, float rotationSpeed)
    : LitTorus(color, reflectionCoef, lightSource, randomRotateAxis(), distance, rotationSpeed)
{
}
LitTorus::LitTorus(Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance, float rotationSpeed)
    : color(color), reflectionCoef(reflectionCoef), _lightSource(lightSource), rotationAxis(rotationAxis), distance(distance), rotationSpeed(rotationSpeed), totalDelta(0)
{
    assert(lightSource != nullptr);
    Rotate(GlEngine::Util::random(3.14159f * 2), randomRotateAxis());
    RequireTick(true);
}
LitTorus::~LitTorus()
{
}

void LitTorus::Tick(float delta)
{
    if (LabControls::isPaused) return;
    else if (!!rotationAxis[0] && !LabControls::rotateZ) return;
    else if (!!rotationAxis[1] && !LabControls::rotateY) return;
    else if (!!rotationAxis[2] && !LabControls::rotateX) return;

    totalDelta += delta;
    auto rotationAmount = totalDelta * rotationSpeed;
    auto transformMatrix = !!rotationAxis[0] ? Matrix<4, 4>::TranslateMatrix({ 0, distance, 0 }) * Matrix<4, 4>::RollMatrix(rotationAmount)  * Matrix<4, 4>::TranslateMatrix(position) :
                           !!rotationAxis[1] ? Matrix<4, 4>::TranslateMatrix({ 0, 0, distance }) * Matrix<4, 4>::YawMatrix(rotationAmount)   * Matrix<4, 4>::TranslateMatrix(position) :
                                               Matrix<4, 4>::TranslateMatrix({ distance, 0, 0 }) * Matrix<4, 4>::PitchMatrix(rotationAmount) * Matrix<4, 4>::TranslateMatrix(position);
    auto transformedPosition = transformMatrix.Transpose() * Vector<4>{ 0, 0, 0, 1 };
    _lightSource->SetPosition({ transformedPosition[0], transformedPosition[1], transformedPosition[2] });
}

std::string LitTorus::name()
{
    return "LitTorus";
}

GlEngine::GraphicsObject *LitTorus::CreateGraphicsObject(GlEngine::GraphicsContext*)
{
    auto mat = new GlEngine::DiffuseMaterial(color, reflectionCoef);
    return GlEngine::ObjGraphicsObject::Create("Resources/torus.obj", mat, { _lightSource });
}

static float randomVecComponent()
{
    return GlEngine::Util::random(2.f) - 1;
}
Vector<3> LitTorus::randomRotateAxis()
{
    while (true)
    {
        Vector<3> axis = { randomVecComponent(), randomVecComponent(), randomVecComponent() };
        if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0) continue;
        if (sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]) > 1) continue;
        return axis;
    }
}
