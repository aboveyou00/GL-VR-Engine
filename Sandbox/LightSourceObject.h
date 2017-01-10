#pragma once

#include "GameObject.h"
#include <map>

namespace GlEngine
{
    class PointLightSource;
}

class LightSourceObject : public GlEngine::GameObject
{
public:
    LightSourceObject(GlEngine::PointLightSource *lightSource = nullptr, float movementSpeed = 4.f);
    ~LightSourceObject();

    virtual void Tick(float delta) override;

    const char *name() override;

    GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

    GlEngine::PointLightSource *lightSource();

private:
    GlEngine::PointLightSource *_lightSource;
    float movementSpeed;
};
