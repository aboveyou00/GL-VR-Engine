#include "stdafx.h"
#include "IChunkProvider.h"
#include "Chunk.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "TileManager.h"

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
        auto tiles = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<TileManager>();
        auto air = tiles->GetTile(0x00);
        auto dirt = tiles->GetTile(0x10);

        auto chunk = new Chunk(x, z);
        for (size_t q = 0; q < Chunk::TILES_PER_CHUNK_X; q++)
            for (size_t w = 0; w < Chunk::TILES_PER_CHUNK_Z; w++)
            {
                chunk->SetTileInfo(q, 0, w, dirt);
                chunk->SetTileInfo(q, 1, w, (rand() % 10 < 9) ? dirt : air);
                chunk->SetTileInfo(q, 2, w, (rand() % 10 < 8) ? dirt : air);
                chunk->SetTileInfo(q, 3, w, (rand() % 10 < 7) ? dirt : air);
                chunk->SetTileInfo(q, 4, w, (rand() % 10 < 6) ? dirt : air);
                chunk->SetTileInfo(q, 5, w, (rand() % 10 < 5) ? dirt : air);
                chunk->SetTileInfo(q, 6, w, (rand() % 10 < 4) ? dirt : air);
                chunk->SetTileInfo(q, 7, w, (rand() % 10 < 3) ? dirt : air);
                chunk->SetTileInfo(q, 8, w, (rand() % 10 < 2) ? dirt : air);
                chunk->SetTileInfo(q, 9, w, (rand() % 10 < 1) ? dirt : air);
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
