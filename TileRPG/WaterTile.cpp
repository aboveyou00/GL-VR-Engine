#include "stdafx.h"
#include "WaterTile.h"
#include "TileManager.h"

#include "Chunk.h"
#include "ChunkGraphicsObject.h"
#include "WaterMaterial.h"

namespace TileRPG
{
    WaterTile::WaterTile()
        : ITile(0x01, false, false)
    {
    }
    WaterTile::~WaterTile()
    {
    }

    SINGLETON_TILE_CPP(WaterTile);

    void WaterTile::AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z)
    {
        chunkGobj.SetMaterial(WaterMaterial::GetInstance());
        
        static const float TILES_PER_TEXTURE_U = 16;
        static const float TILES_PER_TEXTURE_V = 16;

        auto &chunk = chunkGobj.GetChunk();
        auto world = &chunkGobj.GetWorld();

        auto tile = getTile(chunk.GetTileInfo(world, x, y + 1, z));
        if (tile == nullptr || !tile->IsFlushYm())
        {
            //Render face Yp
            auto idx0 = chunkGobj.AddVertex({ x,     y + 0.8f, z },     { x       / TILES_PER_TEXTURE_U, z       / TILES_PER_TEXTURE_V }, { 0, 1, 0 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y + 0.8f, z },     { (x + 1) / TILES_PER_TEXTURE_U, z       / TILES_PER_TEXTURE_V }, { 0, 1, 0 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 0.8f, z + 1 }, { (x + 1) / TILES_PER_TEXTURE_U, (z + 1) / TILES_PER_TEXTURE_V }, { 0, 1, 0 });
            auto idx3 = chunkGobj.AddVertex({ x,     y + 0.8f, z + 1 }, { x       / TILES_PER_TEXTURE_U, (z + 1) / TILES_PER_TEXTURE_V }, { 0, 1, 0 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }
    }
}
