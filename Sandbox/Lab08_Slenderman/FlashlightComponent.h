#pragma once

#include "AudioSourceComponent.h"

namespace GlEngine
{
    class GameObject;

    class SpotlightSource;
}

class FlashlightComponent : public GlEngine::AudioSourceComponent
{
public:
    FlashlightComponent();
    ~FlashlightComponent();

    static GlEngine::GameObject *Create(GlEngine::Frame *frame);

    virtual bool InitializeAsync() override;
    virtual void ShutdownAsync() override;

    virtual void Tick(float delta) override;

    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    GlEngine::SpotlightSource *spotlight();

private:
    GlEngine::SpotlightSource *_spotlight;
    bool _isOn;
    float _power = 1;
};
