#pragma once

#include "AudioListenerComponent.h"
#include <map>
#include "FontRenderer.h"

namespace GlEngine
{
    class AudioSourceComponent;
}

class PageComponent;

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

private:
    std::map<unsigned, bool> keysDown;
    Vector<2> mouseDelta;
    float movementSpeed;
    float rotateSpeed;

    FIG::FontRenderer* renderer;

    unsigned pagesFound = 0;
    std::string renderText;
    float age;

    float &static_amount;
    void UpdateStatic();

    GlEngine::AudioSourceComponent *music, *footsteps, *panting, *staticsfx;
    void UpdateMusic();
    PageComponent *findPageComponent();
    void FindPage(PageComponent *page);
};
