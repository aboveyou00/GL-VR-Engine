#pragma once

#include "GameLoop.h"
#include "IComponent.h"
#include "FrameStack.h"
#include "EventQueue.h"

class SandboxLoop : public GlEngine::GameLoop, public GlEngine::IComponent
{
public:
    SandboxLoop(unsigned targetFPS = 60u);
    ~SandboxLoop();

    bool Initialize();
    void Shutdown();

    const char *name() override;

    inline GlEngine::FrameStack &GetFrameStack()
    {
        return frames;
    }

private:
    bool initLoop();
    void loopBody(float delta);
    void shutdownLoop();

    GlEngine::Events::EventQueue localQueue;
    void copyRemoteQueue();
    void handleEvents();

    GlEngine::FrameStack frames;
    GlEngine::GraphicsContext *ctx;
};
