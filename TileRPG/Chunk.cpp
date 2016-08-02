#include "stdafx.h"
#include "Chunk.h"
#include "World.h"
#include "ITile.h"

namespace TileRPG
{
    Chunk::Chunk(int offx, int offz)
        : x(offx), z(offz), _dirty(false)
    {
    }
    Chunk::~Chunk()
    {
    }

    unsigned Chunk::GetTileInfo(int tileX, int tileY, int tileZ)
    {
        auto miniChunkIdx = tileY / TILES_PER_MINICHUNK_Y;
        return miniChunkOffset(miniChunkIdx, tileX, tileY, tileZ);
    }
    unsigned Chunk::GetTileInfo(World *world, int tileX, int tileY, int tileZ)
    {
        if (tileY < 0) return 0;
        if (tileX < 0 || tileZ < 0 || tileX >= TILES_PER_CHUNK_X || tileZ >= TILES_PER_CHUNK_Z)
            return world->GetTileInfo(tileX + (GetX() * TILES_PER_CHUNK_X), tileY, tileZ + (GetZ() * TILES_PER_CHUNK_Z));
        auto miniChunkIdx = tileY / TILES_PER_MINICHUNK_Y;
        return miniChunkOffset(miniChunkIdx, tileX, tileY, tileZ);
    }
    void Chunk::SetTileInfo(int tileX, int tileY, int tileZ, ITile *tile)
    {
        SetTileInfo(tileX, tileY, tileZ, tile->GetTileId());
    }
    void Chunk::SetTileInfo(int tileX, int tileY, int tileZ, unsigned tile)
    {
        assert(tile >= 0 && tile <= 0xFF);
        if (GetTileInfo(tileX, tileY, tileZ) == tile) return;

        auto miniChunkIdx = tileY / TILES_PER_MINICHUNK_Y;
        auto relativeTileY = tileY - (miniChunkIdx * TILES_PER_MINICHUNK_Y);
        miniChunkOffset(getOrCreateMiniChunk(miniChunkIdx), tileX, relativeTileY, tileZ) = (unsigned char)tile;
    }

    int Chunk::GetMaxY()
    {
        return TILES_PER_MINICHUNK_Y * miniChunks.size();
    }

    Vector<2, int> Chunk::getChunkCoordsFromTileCoords(int x, int z)
    {
        auto int_divide_floor = [](int a, int b) {
            return (a < 0) ? ((a + 1) / b) - 1 : a / b;
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

    unsigned char *&Chunk::getMiniChunk(unsigned idx)
    {
        static unsigned char *null_uchar = nullptr;
        if (idx >= miniChunks.size()) return null_uchar;
        return miniChunks[idx];
    }
    unsigned char *Chunk::getOrCreateMiniChunk(unsigned idx)
    {
        assert(idx < MINICHUNK_MAX_COUNT);
        while (idx >= miniChunks.size()) miniChunks.push_back(nullptr);
        auto &chunk = getMiniChunk(idx);
        if (chunk == nullptr) chunk = new unsigned char[TILES_PER_CHUNK_X * TILES_PER_CHUNK_Z * TILES_PER_MINICHUNK_Y] { 0 };
        return chunk;
    }
    unsigned char Chunk::miniChunkOffset(int miniChunkIdx, int tileX, int tileY, int tileZ)
    {
        auto chunk = getMiniChunk(miniChunkIdx);
        if (chunk == nullptr) return 0;
        return miniChunkOffset(chunk, tileX, tileY - (miniChunkIdx * TILES_PER_MINICHUNK_Y), tileZ);
    }
    unsigned char &Chunk::miniChunkOffset(unsigned char *miniChunk, int tileX, int tileY, int tileZ)
    {
        static const auto TILE_Y_OFF = TILES_PER_CHUNK_X * TILES_PER_CHUNK_Z;
        static const auto TILE_Z_OFF = TILES_PER_CHUNK_X;
        return miniChunk[tileX + (TILE_Y_OFF * tileY) + (TILE_Z_OFF * tileZ)];
    }
}
