#pragma once

#include "GameLoop.h"
#include "IInitializable.h"
#include "FrameStack.h"
#include "EventQueue.h"

class SandboxLoop : public GlEngine::GameLoop, public GlEngine::IInitializable
{
public:
    SandboxLoop(unsigned targetFPS = 200u);
    ~SandboxLoop();

    virtual bool Initialize() override;
    virtual void Shutdown() override;

    virtual std::string name() override;

    GlEngine::FrameStack *frames();

private:
    bool initLoop();
    void loopBody(float delta);
    void shutdownLoop();

    GlEngine::Events::EventQueue localQueue;
    void copyRemoteQueue();
    void handleEvents();

    GlEngine::FrameStack _frames;
};
