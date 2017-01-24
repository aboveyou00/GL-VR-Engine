#pragma once

#include "GameObject.h"
#include <functional>
#include "TemplateMaterial.h"
#include "Material.h"

typedef GlEngine::Material Material;

namespace GlEngine
{
    class PointLightSource;
}

class TemplateTorus : public GlEngine::GameObject
{
public:
    TemplateTorus(TemplateMaterial* mat, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, float distance = 3.f, float rotationSpeed = .5f);
    TemplateTorus(TemplateMaterial* mat, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance = 3.f, float rotationSpeed = .5f);
    ~TemplateTorus();

    virtual void Tick(float delta) override;

    virtual const char *name() override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

private:
    Material* templateMat;

    Vector<3> color;
    Vector<3> reflectionCoef;
    GlEngine::PointLightSource *_lightSource;

    Vector<3> rotationAxis;
    float distance, totalDelta, rotationSpeed;

    static Vector<3> randomRotateAxis();
};
