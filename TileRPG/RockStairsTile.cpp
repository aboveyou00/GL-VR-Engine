#include "stdafx.h"
#include "RockStairsTile.h"
#include "TileManager.h"

namespace TileRPG
{
    RockStairsTile::RockStairsTile()
        : IStairsTile(0x12)
    {
    }
    RockStairsTile::~RockStairsTile()
    {
    }

    SINGLETON_TILE_CPP(RockStairsTile);
}
