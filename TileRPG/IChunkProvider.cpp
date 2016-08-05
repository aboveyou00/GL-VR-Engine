#include "stdafx.h"
#include "IChunkProvider.h"
#include "Chunk.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "TileManager.h"

#include "DirtTile.h"
#include "RockTile.h"
#include "AirTile.h"

namespace TileRPG
{
    IChunkProvider::IChunkProvider()
    {
    }
    IChunkProvider::~IChunkProvider()
    {
    }

    Chunk *IChunkProvider::createDefaultChunk(int x, int z)
    {
        ITile *air = &AirTile::GetInstance();
        ITile *dirt = &DirtTile::GetInstance();
        ITile *rock = &RockTile::GetInstance();

        auto chunk = new Chunk(x, z);
        for (size_t q = 0; q < Chunk::TILES_PER_CHUNK_X; q++)
            for (size_t w = 0; w < Chunk::TILES_PER_CHUNK_Z; w++)
            {
                chunk->SetTileInfo(q, 0, w, dirt);
                chunk->SetTileInfo(q, 1, w, (rand() % 10 < 5) ? dirt : rock);
                chunk->SetTileInfo(q, 2, w, (rand() % 10 < 2) ? rock : air);
            }

        return chunk;
    }
    Chunk *&IChunkProvider::getCache(int x, int z)
    {
        for (size_t q = 0; q < chunkCache.size(); q++)
        {
            auto &chunk = chunkCache[q];
            if (chunk->GetX() == x && chunk->GetZ() == z) return chunk;
        }
        static Chunk *null_chunk = nullptr;
        return null_chunk;
    }
    Chunk *IChunkProvider::putCache(Chunk *chunk)
    {
        int x = chunk->GetX(),
            z = chunk->GetZ();

        auto chunkPtr = &getCache(x, z);
        if (*chunkPtr == nullptr) chunkCache.push_back(chunk);
        else *chunkPtr = chunk;
        //TODO: clean up previous chunk

        return chunk;
    }
}
