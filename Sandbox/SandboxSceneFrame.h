#pragma once

#include "Frame.h"

class SandboxSceneFrame : public GlEngine::Frame
{
public:
    SandboxSceneFrame();
    ~SandboxSceneFrame();

    bool Initialize() override;
    void Shutdown() override;
    void Tick(float delta) override;
};
