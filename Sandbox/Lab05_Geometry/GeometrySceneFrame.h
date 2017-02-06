#pragma once

#include "Frame.h"

class GeometrySceneFrame : public GlEngine::Frame
{
public:
    GeometrySceneFrame();
    ~GeometrySceneFrame();

    virtual bool Initialize() override;
};
