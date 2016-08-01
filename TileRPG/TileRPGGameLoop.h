#pragma once

#include "GameLoop.h"
#include "IComponent.h"
#include "FrameStack.h"
#include "TileManager.h"
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

        inline GlEngine::FrameStack &GetFrameStack()
        {
            return frames;
        }

    private:
        bool initLoop();
        void loopBody(float delta);
        void shutdownLoop();

        GlEngine::Events::EventQueue localQueue;
        void copyRemoteQueue();
        void handleEvents();

        GlEngine::FrameStack frames;
        TileManager *tiles;
    };
}
