#pragma once

#include "AudioListenerComponent.h"
#include <map>

namespace GlEngine
{
    class AudioSourceComponent;
}

class FirstPersonControlsComponent : public GlEngine::AudioListenerComponent
{
public:
    FirstPersonControlsComponent(float movementSpeed = 8.f, float rotateSpeed = 0.005f);
    ~FirstPersonControlsComponent();

    virtual void Tick(float delta) override;
    virtual void UpdateGraphics() override;

    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    virtual void GameObjectChanged() override;

private:
    std::map<unsigned, bool> keysDown;
    Vector<2> mouseDelta;
    float movementSpeed;
    float rotateSpeed;

    GlEngine::AudioSourceComponent *footsteps;
};
