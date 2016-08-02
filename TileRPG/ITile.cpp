#include "stdafx.h"
#include "ITile.h"

#include "Chunk.h"
#include "ChunkGraphicsObject.h"

namespace TileRPG
{
    bool ITile::IsFlushXm()
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushXp()
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushYm()
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushYp()
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushZm()
    {
        return IsFullBlock();
    }
    bool ITile::IsFlushZp()
    {
        return IsFullBlock();
    }

    void ITile::AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z)
    {
        auto &chunk = chunkGobj.GetChunk();
        auto world = &chunkGobj.GetWorld();
        if (chunk.GetTileInfo(world, x - 1, y, z) == 0)
        {
            //Render face Xm
            auto idx0 = chunkGobj.AddVertex({ x, y,     z },     { 0, 0 }, { -1, 0, 0 });
            auto idx1 = chunkGobj.AddVertex({ x, y + 1, z },     { 1, 0 }, { -1, 0, 0 });
            auto idx2 = chunkGobj.AddVertex({ x, y + 1, z + 1 }, { 1, 1 }, { -1, 0, 0 });
            auto idx3 = chunkGobj.AddVertex({ x, y,     z + 1 }, { 0, 1 }, { -1, 0, 0 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }
        if (chunk.GetTileInfo(world, x + 1, y, z) == 0)
        {
            //Render face Xp
            auto idx0 = chunkGobj.AddVertex({ x + 1, y,     z },     { 0, 0 }, { 1, 0, 0 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y + 1, z },     { 1, 0 }, { 1, 0, 0 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z + 1 }, { 1, 1 }, { 1, 0, 0 });
            auto idx3 = chunkGobj.AddVertex({ x + 1, y,     z + 1 }, { 0, 1 }, { 1, 0, 0 });

            chunkGobj.AddTriangle({ idx0, idx2, idx1 });
            chunkGobj.AddTriangle({ idx0, idx3, idx2 });
        }

        if (y > 0 && chunk.GetTileInfo(world, x, y - 1, z) == 0)
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
        if (chunk.GetTileInfo(world, x, y + 1, z) == 0)
        {
            //Render face Yp
            auto idx0 = chunkGobj.AddVertex({ x,     y + 1, z },     { 0, 0 }, { 0, 1, 0 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y + 1, z },     { 1, 0 }, { 0, 1, 0 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z + 1 }, { 1, 1 }, { 0, 1, 0 });
            auto idx3 = chunkGobj.AddVertex({ x,     y + 1, z + 1 }, { 0, 1 }, { 0, 1, 0 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }

        if (chunk.GetTileInfo(world, x, y, z - 1) == 0)
        {
            //Render face Zm
            auto idx0 = chunkGobj.AddVertex({ x,     y,     z }, { 0, 0 }, { 0, 0, -1 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y,     z }, { 1, 0 }, { 0, 0, -1 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z }, { 0, 1 }, { 0, 0, -1 });
            auto idx3 = chunkGobj.AddVertex({ x,     y + 1, z }, { 1, 1 }, { 0, 0, -1 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }
        if (chunk.GetTileInfo(world, x, y, z + 1) == 0)
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
}
