#include "stdafx.h"
#include "GameLogic.h"
#include "World.h"
#include "TileManager.h"
#include "TestSceneFrame.h"

namespace TileRPG
{
    GameLogic::GameLogic(World *world)
        : tiles(new TileManager()), world(world)
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
        if (!world->Initialize())
        {
            tiles->Shutdown();
            return false;
        }

        return true;
    }
    void GameLogic::Shutdown()
    {
        world->Shutdown();
        tiles->Shutdown();

        FrameStack::Shutdown();
    }

    const char *GameLogic::name()
    {
        return "GameLogic";
    }
}
