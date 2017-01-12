#include "stdafx.h"
#include "SandboxLoop.h"
#include "Lab02_Features/FeaturesSceneFrame.h"

#include "Engine.h"
#include "Event.h"
#include "AudioController.h"
#include "ServiceProvider.h"
#include "ILogger.h"

#include "Threading.h"

SandboxLoop::SandboxLoop(unsigned targetFPS)
    : GlEngine::GameLoop(
        [&] { return this->initLoop(); },
        [&](float delta) { return this->loopBody(delta); },
        [&] { return this->shutdownLoop(); },
        targetFPS
      )
{
}
SandboxLoop::~SandboxLoop()
{
}

bool SandboxLoop::Initialize()
{
    RunLoop();
    return true;
}
void SandboxLoop::Shutdown()
{
    StopLoop();
    Join();
}

const char *SandboxLoop::name()
{
    return "SandboxLoop";
}

bool SandboxLoop::initLoop()
{
    this_thread_name() = "logic";
    auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
    logger->Log(GlEngine::LogType::Info, "Beginning logic thread");

    if (!GlEngine::Engine::GetInstance().GetAudioController().Initialize()) return false;

    if (!frames.Initialize()) return false;
    frames.PushNewFrame<FeaturesSceneFrame>();

    return true;
}
void SandboxLoop::loopBody(float delta)
{
    handleEvents();
    frames.Tick(delta);
    GlEngine::Engine::GetInstance().GetAudioController().Tick(0); //We don't need a delta here, YSE worries about its own timing
}
void SandboxLoop::shutdownLoop()
{
    auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
    logger->Log(GlEngine::LogType::Info, "~Terminating logic thread");

    frames.Shutdown();
    GlEngine::Engine::GetInstance().GetAudioController().Shutdown();
}

void SandboxLoop::copyRemoteQueue()
{
    auto &engine = GlEngine::Engine::GetInstance();
    ScopedLock _lock(engine.GetMutex());

    auto &remoteQueue = engine.GetEventQueue();
    GlEngine::Events::Event *evt;
    while ((evt = remoteQueue.RemoveEvent()) != nullptr)
        localQueue.PushEvent(evt);
}
void SandboxLoop::handleEvents()
{
    copyRemoteQueue();
    GlEngine::Events::Event *evt;
    while ((evt = localQueue.RemoveEvent()) != nullptr)
    {
        frames.HandleEvent(*evt);
        delete evt;
    }
}
