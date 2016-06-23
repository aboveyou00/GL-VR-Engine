#pragma once

#include "World.h"
#include "IGameComponent.h"

namespace GlEngine
{
    class GameLoop;
}

namespace TileRPG
{
    class TileManager;

    class GameLogic : public GlEngine::IGameComponent
    {
    public:
        GameLogic();
        ~GameLogic();

        bool Initialize();
        void Tick(float delta);
        void Shutdown();

    private:
        World world;
        TileManager *tiles;
        GlEngine::GameLoop *loop;
    };
}
