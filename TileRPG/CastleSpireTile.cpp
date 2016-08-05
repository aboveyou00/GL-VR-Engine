#include "stdafx.h"
#include "CastleSpireTile.h"
#include "TileManager.h"

namespace TileRPG
{
    CastleSpireTile::CastleSpireTile()
        : ITile(0x1A, true, false)
    {
    }
    CastleSpireTile::~CastleSpireTile()
    {
    }
    
    SINGLETON_TILE_CPP(CastleSpireTile);
}
