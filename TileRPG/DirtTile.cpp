#include "stdafx.h"
#include "DirtTile.h"
#include "TileManager.h"

namespace TileRPG
{
    DirtTile::DirtTile()
        : ITile(0x10, true, true)
    {
    }
    DirtTile::~DirtTile()
    {
    }

    SINGLETON_TILE_CPP(DirtTile);
}
