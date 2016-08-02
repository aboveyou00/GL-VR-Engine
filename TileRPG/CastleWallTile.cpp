#include "stdafx.h"
#include "CastleWallTile.h"
#include "TileManager.h"

namespace TileRPG
{
    CastleWallTile::CastleWallTile()
        : ITile(0x18, true, true)
    {
    }
    CastleWallTile::~CastleWallTile()
    {
    }

    SINGLETON_TILE_CPP(CastleWallTile);
}
