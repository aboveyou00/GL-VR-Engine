#pragma once

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

    GlEngine::GraphicsContext *myCtx;
    GlEngine::Frame *renderedFrame;
    GlEngine::TextureRenderTarget *sceneTex;
};
