#pragma once

#include "GameLoop.h"
#include "IComponent.h"

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
        void LoopBody(float delta);
    };
}
