#pragma once

#include "Frame.h"

class DiffuseSceneFrame : public GlEngine::Frame
{
public:
    DiffuseSceneFrame();
    ~DiffuseSceneFrame();

    bool Initialize() override;
};
