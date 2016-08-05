#pragma once

#include "ITile.h"

namespace TileRPG
{
    class RockTile : public ITile
    {
        SINGLETON_TILE_H(RockTile);

        virtual void AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z) override;
    };
}
