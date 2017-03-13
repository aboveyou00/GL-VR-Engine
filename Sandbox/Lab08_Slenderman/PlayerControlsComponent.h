#pragma once

#include "GameComponent.h"
#include <map>

class PlayerControlsComponent : public GlEngine::GameComponent
{
public:
    PlayerControlsComponent(float movementSpeed = 8.f, float rotateSpeed = 0.005f);
    ~PlayerControlsComponent();

    virtual void Tick(float delta) override;
    virtual void UpdateGraphics() override;

    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    virtual void Render(GlEngine::RenderStage *stage) override;

private:
    std::map<unsigned, bool> keysDown;
    Vector<2> mouseDelta;
    float movementSpeed;
    float rotateSpeed;

    std::string renderText;
    float age;
};
