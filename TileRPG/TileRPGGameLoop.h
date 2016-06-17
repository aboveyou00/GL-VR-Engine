#pragma once

#include "GameLoop.h"
#include "IComponent.h"
#include "EventQueue.h"

namespace TileRPG
{
    class TileRPGGameLoop : public GlEngine::GameLoop, public GlEngine::IComponent
    {
    public:
        TileRPGGameLoop(unsigned targetFPS = 60u);
        ~TileRPGGameLoop();

        bool Initialize();
        void Shutdown();

        int frameIdx = 0;

    private:
        void loopBody(float delta);

        GlEngine::Events::EventQueue localQueue;
        void copyRemoteQueue();
        void handleEvents();
        void dispatchEvent(GlEngine::Events::Event *evt);
    };
}
