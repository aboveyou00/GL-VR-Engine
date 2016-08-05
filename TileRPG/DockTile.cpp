#include "stdafx.h"
#include "DockTile.h"
#include "TileManager.h"

namespace TileRPG
{
    DockTile::DockTile()
        : ITile(0x17, true, false)
    {
    }
    DockTile::~DockTile()
    {
    }

    SINGLETON_TILE_CPP(DockTile);
}
