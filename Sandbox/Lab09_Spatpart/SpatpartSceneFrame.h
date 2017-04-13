#pragma once
#include "Subroutine.h"
#include "Frame.h"

class SpatpartSceneFrame : public GlEngine::Frame
{
public:
    SpatpartSceneFrame();
    ~SpatpartSceneFrame();

    virtual bool Initialize() override;
    virtual void Tick(float dt) override;

    GlEngine::CameraComponent* cameraComponent;
};
