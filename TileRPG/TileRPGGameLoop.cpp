#include "stdafx.h"
#include "TileRPGGameLoop.h"
#include "World.h"
#include "DiskChunkProvider.h"
#include "Event.h"
#include "TestSceneFrame.h"

#include "Threading.h"

#include "Engine.h"
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
        auto &services = GlEngine::Engine::GetInstance().GetServiceProvider();
        if (services.GetService<TileManager>() == nullptr)
        {
            auto mgr = new TileManager();
            if (!mgr->Initialize() || !services.RegisterService(mgr))
            {
                auto logger = services.GetService<GlEngine::ILogger>();
                logger->Log(GlEngine::LogType::Error, "Failed to initialize/register a TileManager service.");
                return false;
            }
        }

        RunLoop();
        frames.PushNewFrame<TestSceneFrame>();
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
        if (!frames.Initialize()) return false;
        this_thread_name() = "gameloop";
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "Beginning game loop thread");
        return true;
    }
    void TileRPGGameLoop::loopBody(float delta)
    {
        handleEvents();
        frames.Tick(delta);
    }
    void TileRPGGameLoop::shutdownLoop()
    {
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "Terminating game loop thread");
        frames.Shutdown();
    }
    void TileRPGGameLoop::copyRemoteQueue()
    {
        GlEngine::Events::Event *evt;
        auto &engine = GlEngine::Engine::GetInstance();
        GlEngine::ScopedLock _lock(engine.GetMutex());

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
