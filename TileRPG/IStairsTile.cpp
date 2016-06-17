#include "stdafx.h"
#include "IStairsTile.h"

namespace TileRPG
{
    IStairsTile::IStairsTile(int tileId)
        : ITile(tileId, true, false)
    {
    }
    IStairsTile::~IStairsTile()
    {
    }
}
