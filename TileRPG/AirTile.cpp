#include "stdafx.h"
#include "AirTile.h"
#include "TileManager.h"

namespace TileRPG
{
    AirTile::AirTile()
        : ITile(0x00, false, false)
    {
    }
    AirTile::~AirTile()
    {
    }

    SINGLETON_TILE_CPP(AirTile);
}
