#pragma once

#include "Frame.h"

class LightsAndEffectsSceneFrame : public GlEngine::Frame
{
public:
    LightsAndEffectsSceneFrame();
    ~LightsAndEffectsSceneFrame();

    bool Initialize() override;
};
