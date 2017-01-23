#pragma once

#include "GameObject.h"

namespace GlEngine
{
    class PointLightSource;
}

class DiscardTorus : public GlEngine::GameObject
{
public:
    DiscardTorus(Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, float distance = 3.f, float rotationSpeed = .5f);
    DiscardTorus(Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance = 3.f, float rotationSpeed = .5f);
    ~DiscardTorus();

    virtual void Tick(float delta) override;

    virtual const char *name() override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

private:
    Vector<3> color;
    Vector<3> reflectionCoef;
    GlEngine::PointLightSource *_lightSource;

    Vector<3> rotationAxis;
    float distance, totalDelta, rotationSpeed;

    static Vector<3> randomRotateAxis();
};
