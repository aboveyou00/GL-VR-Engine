#pragma once

#include "ITile.h"

namespace TileRPG
{
    class SolidAirTile : public ITile
    {
        SINGLETON_TILE_H(SolidAirTile);

        virtual void AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z) override;

        bool IsFlushYm() const override;
    };
}
