#include "stdafx.h"
#include "GameLogic.h"
#include "GameLoop.h"

namespace TileRPG
{
    GameLogic::GameLogic()
        : loop(new GlEngine::GameLoop([&](float delta) { this->Tick(delta); }, 300))
    {
    }
    GameLogic::~GameLogic()
    {
        if (loop != nullptr)
        {
            delete loop;
            loop = nullptr;
        }
    }

    bool GameLogic::Initialize()
    {
        if (!tiles.Initialize()) return false;
        loop->RunLoop();
        return true;
    }
    void GameLogic::Tick(float delta)
    {
        delta;
    }
    void GameLogic::Shutdown()
    {
        loop->StopLoop(false);
        tiles.Shutdown();
    }
}
