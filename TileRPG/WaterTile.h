#pragma once

#include "ITile.h"

namespace TileRPG
{
    class WaterTile : public ITile
    {
        SINGLETON_TILE_H(WaterTile);

        virtual void AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z) override;
    };
}
