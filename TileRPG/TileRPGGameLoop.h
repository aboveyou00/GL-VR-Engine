#pragma once

#include "GameLoop.h"
#include "GameLogic.h"
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

        inline GameLogic &GetGameLogic()
        {
            return _logic;
        }

    private:
        void loopBody(float delta);

        GlEngine::Events::EventQueue localQueue;
        void copyRemoteQueue();
        void handleEvents();

        GameLogic _logic;
    };
}
