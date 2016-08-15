#include "stdafx.h"
#include "TileRPGGameLoop.h"
#include "World.h"
#include "DiskChunkProvider.h"
#include "Event.h"
#include "TestSceneFrame.h"

#include "Threading.h"

#include "Engine.h"
#include "AudioController.h"
#include "ServiceProvider.h"
#include "ILogger.h"

namespace TileRPG
{
    TileRPGGameLoop::TileRPGGameLoop(unsigned targetFPS)
        : GlEngine::GameLoop(
            [&] { return this->initLoop(); },
            [&](float delta) { this->loopBody(delta); },
            [&] { this->shutdownLoop(); }, targetFPS
          )
    {
    }
    TileRPGGameLoop::~TileRPGGameLoop()
    {
    }

    bool TileRPGGameLoop::Initialize()
    {
        RunLoop();
        return true;
    }
    void TileRPGGameLoop::Shutdown()
    {
        StopLoop();
        Join();
    }

    const char *TileRPGGameLoop::name()
    {
        return "TileRPGGameLoop";
    }

    bool TileRPGGameLoop::initLoop()
    {
        this_thread_name() = "gameloop";
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "Beginning game loop thread");

        if (!GlEngine::Engine::GetInstance().GetAudioController().Initialize()) return false;

        if (!frames.Initialize()) return false;
        frames.PushNewFrame<TestSceneFrame>();

        return true;
    }
    void TileRPGGameLoop::loopBody(float delta)
    {
        handleEvents();
        frames.Tick(delta);
        GlEngine::Engine::GetInstance().GetAudioController().Tick(0); //We don't need a delta here, YSE worries about its own timing
    }
    void TileRPGGameLoop::shutdownLoop()
    {
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "~Terminating game loop thread");

        frames.Shutdown();
        GlEngine::Engine::GetInstance().GetAudioController().Shutdown();
    }
    void TileRPGGameLoop::copyRemoteQueue()
    {
        GlEngine::Events::Event *evt;
        auto &engine = GlEngine::Engine::GetInstance();
        ScopedLock _lock(engine.GetMutex());

        auto &remoteQueue = engine.GetEventQueue();
        while ((evt = remoteQueue.RemoveEvent()) != nullptr)
            localQueue.PushEvent(evt);
    }
    void TileRPGGameLoop::handleEvents()
    {
        copyRemoteQueue();
        GlEngine::Events::Event *evt;
        while ((evt = localQueue.RemoveEvent()) != nullptr)
        {
            frames.HandleEvent(*evt);
            delete evt;
        }
    }
}
