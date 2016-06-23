#include "stdafx.h"
#include "GameLogic.h"
#include "GameLoop.h"
#include "TileManager.h"

namespace TileRPG
{
    GameLogic::GameLogic()
        : loop(new GlEngine::GameLoop([&](float delta) { this->Tick(delta); }, 300)),
          tiles(new TileManager())
    {
    }
    GameLogic::~GameLogic()
    {
        Shutdown();
        if (loop != nullptr)
        {
            delete loop;
            loop = nullptr;
        }
        if (tiles != nullptr)
        {
            delete tiles;
            tiles = nullptr;
        }
    }

    bool GameLogic::Initialize()
    {
        if (!tiles->Initialize()) return false;

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
        tiles->Shutdown();
    }
}
