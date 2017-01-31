#pragma once

#include "GameObject.h"
#include <map>

class CameraTargetObject : public GlEngine::GameObject
{
public:
    CameraTargetObject(float movementSpeed = 8.f);
    ~CameraTargetObject();

    void Tick(float delta) override;
    void HandleEvent(GlEngine::Events::Event &evt) override;

    const char *name() override;

    GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;

private:
    std::map<unsigned, bool> keysDown;
    float movementSpeed;
};
