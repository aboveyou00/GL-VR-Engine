#pragma once

#include "ITile.h"

namespace TileRPG
{
    class CastleWallTile : public ITile
    {
        SINGLETON_TILE_H(CastleWallTile);

        void AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z) override;
    };
}
