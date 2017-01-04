#pragma once

#include "World.h"

namespace GlEngine
{
    class Body;
}

namespace TileRPG
{
    class TileCollisionProvider
    {
    public:
        TileCollisionProvider(World * world);
        ~TileCollisionProvider();

        GlEngine::Body * GetBody(int x, int y, int z);
        GlEngine::Body * currentBody;
    
    private:
        World * world;

    };
}