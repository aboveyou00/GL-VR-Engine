#include "stdafx.h"
#include "Chunk.h"

namespace TileRPG
{
    Chunk::Chunk(int offx, int offz)
        : x(offx), z(offz), _dirty(false)
    {
    }
    Chunk::~Chunk()
    {
    }

    ITile *Chunk::GetTileInfo(int tileX, int tileY, int tileZ)
    {
        tileX, tileY, tileZ;
        return nullptr;
    }
    void Chunk::SetTileInfo(int tileX, int tileY, int tileZ, ITile *tile)
    {
        tileX, tileY, tileZ, tile;
    }

    Vector<2, int> Chunk::getChunkCoordsFromTileCoords(int x, int z)
    {
        auto int_divide_floor = [](int a, int b) {
            return (a / b) - (a < 0 ? 1 : 0);
        };
        return {
            int_divide_floor(x, Chunk::TILES_PER_CHUNK_X),
            int_divide_floor(z, Chunk::TILES_PER_CHUNK_Z)
        };
    }
    Vector<2, int> Chunk::getChunkDimensionsFromTileDimensions(int x, int z)
    {
        //Not intended for uce with negative numbers
        auto int_divide_ceil = [](int a, int b) {
            return (a + b - 1) / b;
        };
        return {
            int_divide_ceil(x, Chunk::TILES_PER_CHUNK_X),
            int_divide_ceil(z, Chunk::TILES_PER_CHUNK_Z)
        };
    }
}
