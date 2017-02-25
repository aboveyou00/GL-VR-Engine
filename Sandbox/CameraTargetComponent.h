#pragma once

#include "GameComponent.h"
#include "CameraComponent.h"
#include <map>

class CameraTargetComponent : public GlEngine::GameComponent
{
public:
    CameraTargetComponent(float movementSpeed = 8.f);
    ~CameraTargetComponent();

    virtual void Tick(float delta) override;
    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

private:
    std::map<unsigned, bool> keysDown;
    Vector<2> mouseDelta;
    float movementSpeed;
};
