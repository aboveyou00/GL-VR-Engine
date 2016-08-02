#include "stdafx.h"
#include "FlowingWaterTile.h"
#include "TileManager.h"

namespace TileRPG
{
    FlowingWaterTile::FlowingWaterTile()
        : ITile(0x02, false, false)
    {
    }
    FlowingWaterTile::~FlowingWaterTile()
    {
    }

    SINGLETON_TILE_CPP(FlowingWaterTile);
}
