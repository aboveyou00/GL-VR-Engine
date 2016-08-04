#include "stdafx.h"
#include "ITile.h"

#include "Chunk.h"
#include "ChunkGraphicsObject.h"
#include "TileManager.h"

namespace TileRPG
{
    bool ITile::IsFlushXm() const
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushXp() const
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushYm() const
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushYp() const
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushZm() const
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushZp() const
    {
        return IsFullBlock();
    }

    void ITile::AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z)
    {
        auto &chunk = chunkGobj.GetChunk();
        auto world = &chunkGobj.GetWorld();
        ITile *tile;
        tile = getTile(chunk.GetTileInfo(world, x - 1, y, z));
        if (tile == nullptr || !tile->IsFlushXp())
        {
            //Render face Xm
            auto idx0 = chunkGobj.AddVertex({ x, y,     z },     { 0, 0 }, { -1, 0, 0 });
            auto idx1 = chunkGobj.AddVertex({ x, y + 1, z },     { 1, 0 }, { -1, 0, 0 });
            auto idx2 = chunkGobj.AddVertex({ x, y + 1, z + 1 }, { 1, 1 }, { -1, 0, 0 });
            auto idx3 = chunkGobj.AddVertex({ x, y,     z + 1 }, { 0, 1 }, { -1, 0, 0 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }
        tile = getTile(chunk.GetTileInfo(world, x + 1, y, z));
        if (tile == nullptr || !tile->IsFlushXm())
        {
            //Render face Xp
            auto idx0 = chunkGobj.AddVertex({ x + 1, y,     z },     { 0, 0 }, { 1, 0, 0 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y + 1, z },     { 1, 0 }, { 1, 0, 0 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z + 1 }, { 1, 1 }, { 1, 0, 0 });
            auto idx3 = chunkGobj.AddVertex({ x + 1, y,     z + 1 }, { 0, 1 }, { 1, 0, 0 });

            chunkGobj.AddTriangle({ idx0, idx2, idx1 });
            chunkGobj.AddTriangle({ idx0, idx3, idx2 });
        }

        tile = (y == 0) ? nullptr : getTile(chunk.GetTileInfo(world, x, y - 1, z));
        if (tile == nullptr || !tile->IsFlushYp())
        {
            //TODO: Do I really need Ym? Ever? This may just be wasted tris
            //Render face Ym
            auto idx0 = chunkGobj.AddVertex({ x,     y, z },     { 0, 0 }, { 0, -1, 0 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y, z },     { 1, 0 }, { 0, -1, 0 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y, z + 1 }, { 1, 1 }, { 0, -1, 0 });
            auto idx3 = chunkGobj.AddVertex({ x,     y, z + 1 }, { 0, 1 }, { 0, -1, 0 });

            chunkGobj.AddTriangle({ idx0, idx2, idx1 });
            chunkGobj.AddTriangle({ idx0, idx3, idx2 });
        }
        tile = getTile(chunk.GetTileInfo(world, x, y + 1, z));
        if (tile == nullptr || !tile->IsFlushYm())
        {
            //Render face Yp
            auto idx0 = chunkGobj.AddVertex({ x,     y + 1, z },     { 0, 0 }, { 0, 1, 0 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y + 1, z },     { 1, 0 }, { 0, 1, 0 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z + 1 }, { 1, 1 }, { 0, 1, 0 });
            auto idx3 = chunkGobj.AddVertex({ x,     y + 1, z + 1 }, { 0, 1 }, { 0, 1, 0 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }

        tile = getTile(chunk.GetTileInfo(world, x, y, z - 1));
        if (tile == nullptr || !tile->IsFlushZp())
        {
            //Render face Zm
            auto idx0 = chunkGobj.AddVertex({ x,     y,     z }, { 0, 0 }, { 0, 0, -1 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y,     z }, { 1, 0 }, { 0, 0, -1 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z }, { 0, 1 }, { 0, 0, -1 });
            auto idx3 = chunkGobj.AddVertex({ x,     y + 1, z }, { 1, 1 }, { 0, 0, -1 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }
        tile = getTile(chunk.GetTileInfo(world, x, y, z + 1));
        if (tile == nullptr || !tile->IsFlushZm())
        {
            //Render face Zp
            auto idx0 = chunkGobj.AddVertex({ x,     y,     z + 1 }, { 0, 0 }, { 0, 0, 1 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y,     z + 1 }, { 1, 0 }, { 0, 0, 1 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z + 1 }, { 0, 1 }, { 0, 0, 1 });
            auto idx3 = chunkGobj.AddVertex({ x,     y + 1, z + 1 }, { 1, 1 }, { 0, 0, 1 });

            chunkGobj.AddTriangle({ idx0, idx2, idx1 });
            chunkGobj.AddTriangle({ idx0, idx3, idx2 });
        }
    }

    const char *ITile::footstep_sound()
    {
        return "Audio/footstep-grass.wav";
    }

    ITile *ITile::getTile(int tileId)
    {
        auto &tileManager = TileManager::GetInstance();
        return tileManager.GetTile(tileId);
    }
}
