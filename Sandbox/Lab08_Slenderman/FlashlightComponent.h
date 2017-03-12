#pragma once

#include "GameComponent.h"

namespace GlEngine
{
    class GameObject;

    class SpotlightSource;
}

class FlashlightComponent : public GlEngine::GameComponent
{
public:
    FlashlightComponent();
    ~FlashlightComponent();

    static GlEngine::GameObject *Create(GlEngine::Frame *frame);

    virtual bool InitializeAsync() override;
    virtual void ShutdownAsync() override;

    virtual void Tick(float delta) override;

    GlEngine::SpotlightSource *spotlight();

private:
    GlEngine::SpotlightSource *_spotlight;
};
