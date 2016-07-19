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

        const char *name() override;

        inline GameLogic &GetGameLogic()
        {
            return _logic;
        }

    private:
        bool initLoop();
        void loopBody(float delta);
        void shutdownLoop();

        GlEngine::Events::EventQueue localQueue;
        void copyRemoteQueue();
        void handleEvents();

        GameLogic _logic;
    };
}
