#include "stdafx.h"
#include "RoadTile.h"
#include "TileManager.h"

namespace TileRPG
{
    RoadTile::RoadTile()
        : ITile(0x15, true, false)
    {
    }
    RoadTile::~RoadTile()
    {
    }

    SINGLETON_TILE_CPP(RoadTile);
}
