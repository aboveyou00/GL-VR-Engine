#pragma once

#include "Frame.h"
#include "ComponentArray.h"
#include <map>

namespace GlEngine
{
    class Texture;
}
namespace GlEngine::ShaderFactory
{
    class ShaderProp;
}

class DistortionSceneFrame : public GlEngine::Frame
{
public:
    DistortionSceneFrame();
    ~DistortionSceneFrame();

    virtual bool Initialize() override;

private:
    std::map<size_t, GlEngine::ShaderFactory::ShaderProp*> props;
    GlEngine::ShaderFactory::ShaderSource distortSource;
    GlEngine::Texture *sceneTex;
};
