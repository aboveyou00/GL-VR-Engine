#include "stdafx.h"

#include "PhongTorus.h"
#include "ObjGraphicsObject.h"
#include "PhongMaterial.h"
#include "RandomUtils.h"
#include "MatrixStack.h"
#include "AmbientLightSource.h"
#include "PointLightSource.h"
#include "PhongFlatMaterial.h"
#include "../LabControls.h"

PhongTorus::PhongTorus(Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, float distance, float rotationSpeed, bool flat)
    : PhongTorus(color, reflectionCoef, lightSource, randomRotateAxis(), distance, rotationSpeed, flat)
{
}
PhongTorus::PhongTorus(Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance, float rotationSpeed, bool flat)
    : color(color), reflectionCoef(reflectionCoef), _lightSource(lightSource), rotationAxis(rotationAxis), distance(distance), rotationSpeed(rotationSpeed), totalDelta(0), flat(flat)
{
    assert(lightSource != nullptr);
    Rotate(GlEngine::Util::random(3.14159f * 2), randomRotateAxis());
    RequireTick(true);
}
PhongTorus::~PhongTorus()
{
}

void PhongTorus::Tick(float delta)
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

const char *PhongTorus::name()
{
    return "PhongTorus";
}

GlEngine::GraphicsObject *PhongTorus::CreateGraphicsObject(GlEngine::GraphicsContext *ctx)
{
    ctx;
    GlEngine::Material* mat = flat ? (GlEngine::Material*)new PhongFlatMaterial(color, reflectionCoef) : new GlEngine::PhongMaterial(color, reflectionCoef);
    return GlEngine::ObjGraphicsObject::Create("Resources/torus.obj", mat, { new GlEngine::AmbientLightSource({ .1f, .1f, .1f }), _lightSource });
}

static float randomVecComponent()
{
    return GlEngine::Util::random(2.f) - 1;
}
Vector<3> PhongTorus::randomRotateAxis()
{
    while (true)
    {
        Vector<3> axis = { randomVecComponent(), randomVecComponent(), randomVecComponent() };
        if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0) continue;
        if (sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]) > 1) continue;
        return axis;
    }
}
