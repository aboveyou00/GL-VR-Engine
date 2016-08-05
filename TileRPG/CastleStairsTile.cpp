#include "stdafx.h"
#include "CastleStairsTile.h"
#include "TileManager.h"

namespace TileRPG
{
    CastleStairsTile::CastleStairsTile()
        : IStairsTile(0x19)
    {
    }
    CastleStairsTile::~CastleStairsTile()
    {
    }

    SINGLETON_TILE_CPP(CastleStairsTile);
}
