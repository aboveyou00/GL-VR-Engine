#include "stdafx.h"
#include "LitTorus.h"
#include "ObjGraphicsObject.h"
#include "DiffuseMaterial.h"
#include <random>

LitTorus::LitTorus(Vector<3> color, Vector<3> reflectionCoef, float rotationSpeed)
    : LitTorus(color, reflectionCoef, rotationSpeed, randomRotateAxis())
{
    RequireTick(true);
}
LitTorus::LitTorus(Vector<3> color, Vector<3> reflectionCoef, float rotationSpeed, Vector<3> rotationAxis)
    : color(color), reflectionCoef(reflectionCoef), rotationSpeed(rotationSpeed), rotationAxis(rotationAxis)
{
}
LitTorus::~LitTorus()
{
}

void LitTorus::Tick(float delta)
{
    this->Rotate(delta * rotationSpeed, rotationAxis);
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
    auto val = (float)rand() / (float)RAND_MAX;
    return (val - .5f) * 2;
}
Vector<3> LitTorus::randomRotateAxis()
{
    while (true)
    {
        Vector<3> axis = { randomVecComponent(), randomVecComponent(), randomVecComponent() };
        if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0) continue;
        //if ()
        return axis;
    }
}
