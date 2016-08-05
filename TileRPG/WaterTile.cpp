#include "stdafx.h"
#include "WaterTile.h"
#include "TileManager.h"

namespace TileRPG
{
    WaterTile::WaterTile()
        : ITile(0x01, false, false)
    {
    }
    WaterTile::~WaterTile()
    {
    }

    SINGLETON_TILE_CPP(WaterTile);
}
