#include "stdafx.h"
#include "TileRPGGameLoop.h"

namespace TileRPG
{
    TileRPGGameLoop::TileRPGGameLoop(unsigned targetFPS)
        : GlEngine::GameLoop([&](float delta) { this->LoopBody(delta); }, targetFPS)
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

    void TileRPGGameLoop::LoopBody(float delta)
    {
        delta;
        frameIdx++;
    }
}
