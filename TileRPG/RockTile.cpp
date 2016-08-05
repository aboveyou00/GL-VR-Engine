#include "stdafx.h"
#include "RockTile.h"
#include "TileManager.h"

namespace TileRPG
{
    RockTile::RockTile()
        : ITile(0x11, true, true)
    {
    }
    RockTile::~RockTile()
    {
    }

    SINGLETON_TILE_CPP(RockTile);
}
