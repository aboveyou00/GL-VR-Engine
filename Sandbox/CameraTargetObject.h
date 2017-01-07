#pragma once

#include "GameObject.h"
#include <map>

class CameraTargetObject : public GlEngine::GameObject
{
public:
    CameraTargetObject(float movementSpeed = 8.f);
    ~CameraTargetObject();

    const char *name() override;

    void Tick(float delta) override;
    void HandleEvent(GlEngine::Events::Event &evt) override;

    GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

private:
    std::map<unsigned, bool> keysDown;
    float movementSpeed;
};
