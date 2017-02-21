#pragma once

#include "GameComponent.h"
#include <map>

class CameraTargetComponent : public GlEngine::GameComponent
{
public:
    CameraTargetComponent(float movementSpeed = 8.f);
    ~CameraTargetComponent();

    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, float movementSpeed = 8.f);

    virtual void Tick(float delta) override;
    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

private:
    std::map<unsigned, bool> keysDown;
    float movementSpeed;
};
