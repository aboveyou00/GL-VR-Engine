#include "stdafx.h"
#include "LitTorus.h"
#include "ObjGraphicsObject.h"
#include "DiffuseMaterial.h"
#include "RandomUtils.h"
#include "MatrixStack.h"

LitTorus::LitTorus(Vector<3> color, Vector<3> reflectionCoef, float rotationSpeed)
    : LitTorus(color, reflectionCoef, rotationSpeed, randomRotateAxis())
{
}
LitTorus::LitTorus(Vector<3> color, Vector<3> reflectionCoef, float rotationSpeed, Vector<3> rotationAxis)
    : color(color), reflectionCoef(reflectionCoef), rotationSpeed(rotationSpeed), rotationAxis(rotationAxis)
{
    RequireTick(true);
    std::cout << "Rotation Axis: " << rotationAxis << std::endl;
}
LitTorus::~LitTorus()
{
}

void LitTorus::Tick(float delta)
{
    this->Rotate(rotationSpeed * delta, rotationAxis);
}

const char *LitTorus::name()
{
    return "LitTorus";
}

GlEngine::GraphicsObject *LitTorus::CreateGraphicsObject(GlEngine::GraphicsContext &ctx)
{
    ctx;
    return GlEngine::ObjGraphicsObject::Create("Resources/torus.obj", new GlEngine::DiffuseMaterial(color, reflectionCoef));
}

float randomVecComponent()
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
