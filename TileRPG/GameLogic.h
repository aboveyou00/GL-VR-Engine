#pragma once

#include "IGameComponent.h"

#include "Event.h"

#include "GameObject.h"
#include <vector>
#include "FrameStack.h"

namespace GlEngine
{
    class GameLoop;
}

namespace TileRPG
{
    class TileManager;
    class World;

    class GameLogic : public GlEngine::FrameStack
    {
    public:
        GameLogic(World *world);
        ~GameLogic();

        bool Initialize() override;
        void Shutdown() override;

        const char *name() override;

    private:
        World *world;
        TileManager *tiles;
    };
}
