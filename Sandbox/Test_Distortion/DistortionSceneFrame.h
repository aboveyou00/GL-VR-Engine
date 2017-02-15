#pragma once

#include "Subroutine.h"
#include "Frame.h"
#include "ComponentArray.h"
#include <map>

namespace GlEngine
{
    class TextureRenderTarget;
    class GraphicsContext;
}
namespace GlEngine::Events
{
    class Event;
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
    virtual void Tick(float delta) override;
    virtual void Shutdown() override;

    virtual void HandleEvent(GlEngine::Events::Event &evt);

private:
    std::map<size_t, GlEngine::ShaderFactory::ShaderProp*> props;
    GlEngine::ShaderFactory::ShaderSource distortSource;
    unsigned sr_index;
    static const unsigned SR_COUNT = 6;
    GlEngine::ShaderFactory::Subroutine *subroutines[SR_COUNT] = {
        new GlEngine::ShaderFactory::Subroutine("SinWave"),
        new GlEngine::ShaderFactory::Subroutine("GaussianBlur"),
        new GlEngine::ShaderFactory::Subroutine("DetectEdge"),
        new GlEngine::ShaderFactory::Subroutine("Deconvolution"),
        new GlEngine::ShaderFactory::Subroutine("MedianFiltering"),
        new GlEngine::ShaderFactory::Subroutine("UnsharpMasking")
    };
    GlEngine::ShaderFactory::Subroutine *currentSubroutine;

    GlEngine::GraphicsContext *myCtx;
    GlEngine::Frame *renderedFrame;
    GlEngine::TextureRenderTarget *sceneTex;
};
