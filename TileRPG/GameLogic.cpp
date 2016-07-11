#include "stdafx.h"
#include "GameLogic.h"
#include "GameLoop.h"
#include "TileManager.h"

#include "TestSceneFrame.h"

namespace TileRPG
{
    GameLogic::GameLogic()
        : tiles(new TileManager())
    {
    }
    GameLogic::~GameLogic()
    {
        Shutdown();
        if (tiles != nullptr)
        {
            delete tiles;
            tiles = nullptr;
        }
    }

    bool GameLogic::Initialize()
    {
        if (!FrameStack::Initialize()) return false;
        this->PushNewFrame<TestSceneFrame>();

        if (!tiles->Initialize()) return false;

        return true;
    }
    void GameLogic::Shutdown()
    {
        tiles->Shutdown();

        FrameStack::Shutdown();
    }
}
