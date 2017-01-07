#include "stdafx.h"
#include "TileCollision.h"

namespace GlEngine
{
    TileCollision::TileCollision(Body* bodyA, Body* bodyB, unsigned side, int tileId)
        : BoxCollision(bodyA, bodyB, side), tileId(tileId)
    {
    }
    TileCollision::~TileCollision()
    {
    }
    int TileCollision::id()
    {
        return 2;
    }
}