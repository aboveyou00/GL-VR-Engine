#include "stdafx.h"
#include "TileRPGGameLoop.h"
#include "World.h"
#include "DiskChunkProvider.h"

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
          ),
          _logic(new World(new DiskChunkProvider("world")))
    {
    }
    TileRPGGameLoop::~TileRPGGameLoop()
    {
    }

    bool TileRPGGameLoop::Initialize()
    {
        if (!_logic.Initialize()) return false;
        RunLoop();
        return true;
    }
    void TileRPGGameLoop::Shutdown()
    {
        StopLoop();
        Join();
        _logic.Shutdown();
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
        return true;
    }
    void TileRPGGameLoop::loopBody(float delta)
    {
        handleEvents();
        _logic.Tick(delta);
    }
    void TileRPGGameLoop::shutdownLoop()
    {
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "Terminating game loop thread");
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
            _logic.HandleEvent(*evt);
            delete evt;
        }
    }
}
