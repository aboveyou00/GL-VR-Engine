#pragma once

#include "ITile.h"

namespace TileRPG
{
    class DirtTile : public ITile
    {
        SINGLETON_TILE_H(DirtTile);

        virtual void AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z) override;
    };
}
