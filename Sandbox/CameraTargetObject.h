#pragma once

#include "GameObject.h"
#include <map>

namespace GlEngine
{
    class CameraGameObject;
}

class CameraTargetObject : public GlEngine::GameObject
{
public:
    CameraTargetObject(GlEngine::CameraGameObject *camera, float movementSpeed = 8.f);
    ~CameraTargetObject();

    virtual void Tick(float delta) override;
    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    virtual std::string name() override;

    GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;

private:
    std::map<unsigned, bool> keysDown;
    float movementSpeed, facingAngle, elevationAngle;
    GlEngine::CameraGameObject *camera;
};
