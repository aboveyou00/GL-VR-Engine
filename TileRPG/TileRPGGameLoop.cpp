#include "stdafx.h"
#include "TileRPGGameLoop.h"

#include "Threading.h"

#include "Engine.h"
#include "Event.h"

namespace TileRPG
{
    TileRPGGameLoop::TileRPGGameLoop(unsigned targetFPS)
        : GlEngine::GameLoop([&](float delta) { this->loopBody(delta); }, targetFPS)
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

    void TileRPGGameLoop::loopBody(float delta)
    {
        delta;

        handleEvents();
        frameIdx++;
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
            dispatchEvent(evt);
    }
    void TileRPGGameLoop::dispatchEvent(GlEngine::Events::Event *evt)
    {
        
        delete evt;
    }
}
