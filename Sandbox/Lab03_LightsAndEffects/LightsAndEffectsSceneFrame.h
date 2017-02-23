#pragma once

#include "Frame.h"

namespace GlEngine
{
    class SpotlightSource;
}

class LightsAndEffectsSceneFrame : public GlEngine::Frame
{
public:
    LightsAndEffectsSceneFrame();
    ~LightsAndEffectsSceneFrame();

    virtual bool Initialize() override;

    virtual void Tick(float delta) override;

private:
    float totalDelta;
    GlEngine::SpotlightSource *spotLightSource;
};
