#pragma once

#include "TileManager.h"
#include "World.h"
#include "IGameComponent.h"

namespace GlEngine
{
    class GameLoop;
}

namespace TileRPG
{
    class GameLogic : public GlEngine::IGameComponent
    {
    public:
        GameLogic();
        ~GameLogic();

        bool Initialize();
        void Tick(float delta);
        void Shutdown();

    private:
        TileManager tiles;
        World world;
        GlEngine::GameLoop *loop;
    };
}
