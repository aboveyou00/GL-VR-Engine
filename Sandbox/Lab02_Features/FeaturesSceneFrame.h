#pragma once

#include "Frame.h"

class FeaturesSceneFrame : public GlEngine::Frame
{
public:
    FeaturesSceneFrame();
    ~FeaturesSceneFrame();

    bool Initialize() override;
};
