#pragma once

#include "Frame.h"

class ParticlesSceneFrame : public GlEngine::Frame
{
public:
    ParticlesSceneFrame();
    ~ParticlesSceneFrame();

    virtual bool Initialize() override;
};
