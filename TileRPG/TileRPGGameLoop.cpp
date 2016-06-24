#include "stdafx.h"
#include "TileRPGGameLoop.h"

#include "Threading.h"

#include "Engine.h"

namespace TileRPG
{
    TileRPGGameLoop::TileRPGGameLoop(unsigned targetFPS)
        : GlEngine::GameLoop([] { this_thread_name() = "gameloop"; return true; }, [&](float delta) { this->loopBody(delta); }, nullptr, targetFPS)
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

    void TileRPGGameLoop::loopBody(float delta)
    {
        handleEvents();
        _logic.Tick(delta);
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
            _logic.DispatchEvent(evt);
            delete evt;
        }
    }
}
