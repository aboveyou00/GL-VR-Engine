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

        virtual bool Initialize();
        virtual void Shutdown();

        virtual std::string name() override;

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
    };
}
