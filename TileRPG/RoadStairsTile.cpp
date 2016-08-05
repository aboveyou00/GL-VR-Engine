#include "stdafx.h"
#include "RoadStairsTile.h"
#include "TileManager.h"

namespace TileRPG
{
    RoadStairsTile::RoadStairsTile()
        : IStairsTile(0x16)
    {
    }
    RoadStairsTile::~RoadStairsTile()
    {
    }

    SINGLETON_TILE_CPP(RoadStairsTile);
}
