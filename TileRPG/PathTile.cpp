#include "stdafx.h"
#include "PathTile.h"
#include "TileManager.h"

namespace TileRPG
{
    PathTile::PathTile()
        : ITile(0x13, true, false)
    {
    }
    PathTile::~PathTile()
    {
    }

    SINGLETON_TILE_CPP(PathTile);
}
