#pragma once

#include "GameObject.h"

class LitTorus : public GlEngine::GameObject
{
public:
    LitTorus(Vector<3> color, Vector<3> reflectionCoef, float rotationSpeed);
    LitTorus(Vector<3> color, Vector<3> reflectionCoef, float rotationSpeed, Vector<3> rotationAxis);
    ~LitTorus();

    virtual void Tick(float delta) override;

    virtual const char *name() override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

private:
    Vector<3> color;
    Vector<3> reflectionCoef;
    float rotationSpeed;
    Vector<3> rotationAxis;

    static Vector<3> randomRotateAxis();
};
