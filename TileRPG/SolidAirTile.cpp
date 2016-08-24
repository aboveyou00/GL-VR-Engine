#include "stdafx.h"
#include "SolidAirTile.h"
#include "TileManager.h"

namespace TileRPG
{
    SolidAirTile::SolidAirTile()
        : ITile(0xFF, true, true)
    {
    }
    SolidAirTile::~SolidAirTile()
    {
    }

    SINGLETON_TILE_CPP(SolidAirTile);

    void SolidAirTile::AddToChunkGraphicsObject(ChunkGraphicsObject&, int, int, int)
    {
    }

    bool SolidAirTile::IsFlushYm() const
    {
        return false;
    }
}
