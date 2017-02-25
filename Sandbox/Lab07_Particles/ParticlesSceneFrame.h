#pragma once

#include "Frame.h"

namespace GlEngine
{
    class Texture;
}

class ParticlesSceneFrame : public GlEngine::Frame
{
public:
    ParticlesSceneFrame();
    ~ParticlesSceneFrame();

    virtual bool Initialize() override;

private:
    GlEngine::Texture *particleTex;
};
