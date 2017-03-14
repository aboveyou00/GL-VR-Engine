#pragma once

#include "AudioListenerComponent.h"
#include <map>

namespace GlEngine
{
    class AudioSourceComponent;
}

class PlayerControlsComponent : public GlEngine::AudioListenerComponent
{
public:
    PlayerControlsComponent(float *static_amount, float movementSpeed = 8.f, float rotateSpeed = 0.005f);
    ~PlayerControlsComponent();

    virtual void Tick(float delta) override;
    virtual void UpdateGraphics() override;

    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    virtual void Render(GlEngine::RenderStage *stage) override;

    virtual void GameObjectChanged() override;

    void FindPage();

private:
    std::map<unsigned, bool> keysDown;
    Vector<2> mouseDelta;
    float movementSpeed;
    float rotateSpeed;

    unsigned pagesFound = 0;
    std::string renderText;
    float age;

    float &static_amount;

    GlEngine::AudioSourceComponent *music, *footsteps, *panting, *staticsfx;
    void UpdateMusic();
};
