#pragma once

#include "IStairsTile.h"

namespace TileRPG
{
    class CastleStairsTile : public IStairsTile
    {
        SINGLETON_TILE_H(CastleStairsTile);

        void AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z) override;
    };
}
