#pragma once

#include "Subroutine.h"
#include "Frame.h"
#include "ComponentArray.h"
#include <map>

namespace GlEngine
{
    class TextureRenderTarget;
}
namespace GlEngine::Events
{
    class Event;
}
namespace GlEngine::ShaderFactory
{
    class ShaderProp;
}

class SlendermanSceneFrame;

class SlendermanStaticSceneFrame : public GlEngine::Frame
{
public:
    SlendermanStaticSceneFrame();
    ~SlendermanStaticSceneFrame();

    virtual bool Initialize() override;
    virtual void Tick(float delta) override;
    virtual void Shutdown() override;

    virtual void HandleEvent(GlEngine::Events::Event &evt);

private:
    SlendermanSceneFrame *renderedFrame;
    GlEngine::TextureRenderTarget *sceneTex;
};
