#include "stdafx.h"
#include "PathStairsTile.h"
#include "TileManager.h"

namespace TileRPG
{
    PathStairsTile::PathStairsTile()
        : IStairsTile(0x14)
    {
    }
    PathStairsTile::~PathStairsTile()
    {
    }

    SINGLETON_TILE_CPP(PathStairsTile);
}
