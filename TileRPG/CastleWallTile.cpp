#include "stdafx.h"
#include "CastleWallTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "Shader.h"
#include "Texture.h"
#include "FbxGraphicsObject.h"

#include "Chunk.h"
#include "World.h"

namespace TileRPG
{
    CastleWallTile::CastleWallTile()
        : ITile(0x18, true, true)
    {
    }
    CastleWallTile::~CastleWallTile()
    {
    }

    SINGLETON_TILE_CPP(CastleWallTile);

    void CastleWallTile::AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z)
    {
        static auto shader = GlEngine::Shader::Create("Shaders", "direct_light_tex");
        static auto texture_wall = GlEngine::Texture::FromFile("Textures/castle_wall.png");
        static auto texture_floor = GlEngine::Texture::FromFile("Textures/castle_floor.png");
        static auto castle_none_top = GlEngine::FbxGraphicsObject<Matrix<4, 4>>::Create("Resources/castle_none_top.fbx");
        
        static const float TILES_PER_TEXTURE_U = 2;
        static const float TILES_PER_TEXTURE_V = 2;

        auto &chunk = chunkGobj.GetChunk();
        auto world = &chunkGobj.GetWorld();
        ITile *tile;

        tile = getTile(chunk.GetTileInfo(world, x, y + 1, z));
        if (tile == nullptr || !tile->IsFlushYm())
        {
            chunkGobj.AddInstance(castle_none_top, Matrix<4, 4>::TranslateMatrix(x + .5f, (float)y, z + .5f));
            return;
        }

        chunkGobj.SetGraphics(shader, texture_wall);
        tile = getTile(chunk.GetTileInfo(world, x - 1, y, z));
        if (tile == nullptr || !tile->IsFlushXp())
        {
            //Render face Xm
            auto idx0 = chunkGobj.AddVertex({ x, y,     z },     { z       / TILES_PER_TEXTURE_U, y       / TILES_PER_TEXTURE_V }, { -1, 0, 0 });
            auto idx1 = chunkGobj.AddVertex({ x, y + 1, z },     { z       / TILES_PER_TEXTURE_U, (y + 1) / TILES_PER_TEXTURE_V }, { -1, 0, 0 });
            auto idx2 = chunkGobj.AddVertex({ x, y + 1, z + 1 }, { (z + 1) / TILES_PER_TEXTURE_U, (y + 1) / TILES_PER_TEXTURE_V }, { -1, 0, 0 });
            auto idx3 = chunkGobj.AddVertex({ x, y,     z + 1 }, { (z + 1) / TILES_PER_TEXTURE_U, y       / TILES_PER_TEXTURE_V }, { -1, 0, 0 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }
        tile = getTile(chunk.GetTileInfo(world, x + 1, y, z));
        if (tile == nullptr || !tile->IsFlushXm())
        {
            //Render face Xp
            auto idx0 = chunkGobj.AddVertex({ x + 1, y,     z },     { z       / TILES_PER_TEXTURE_U, y       / TILES_PER_TEXTURE_V }, { 1, 0, 0 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y + 1, z },     { z       / TILES_PER_TEXTURE_U, (y + 1) / TILES_PER_TEXTURE_V }, { 1, 0, 0 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z + 1 }, { (z + 1) / TILES_PER_TEXTURE_U, (y + 1) / TILES_PER_TEXTURE_V }, { 1, 0, 0 });
            auto idx3 = chunkGobj.AddVertex({ x + 1, y,     z + 1 }, { (z + 1) / TILES_PER_TEXTURE_U, y       / TILES_PER_TEXTURE_V }, { 1, 0, 0 });

            chunkGobj.AddTriangle({ idx0, idx2, idx1 });
            chunkGobj.AddTriangle({ idx0, idx3, idx2 });
        }

        tile = getTile(chunk.GetTileInfo(world, x, y, z - 1));
        if (tile == nullptr || !tile->IsFlushZp())
        {
            //Render face Zm
            auto idx0 = chunkGobj.AddVertex({ x,     y,     z }, { x       / TILES_PER_TEXTURE_U, y       / TILES_PER_TEXTURE_V }, { 0, 0, -1 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y,     z }, { (x + 1) / TILES_PER_TEXTURE_U, y       / TILES_PER_TEXTURE_V }, { 0, 0, -1 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z }, { (x + 1) / TILES_PER_TEXTURE_U, (y + 1) / TILES_PER_TEXTURE_V }, { 0, 0, -1 });
            auto idx3 = chunkGobj.AddVertex({ x,     y + 1, z }, { x       / TILES_PER_TEXTURE_U, (y + 1) / TILES_PER_TEXTURE_V }, { 0, 0, -1 });

            chunkGobj.AddTriangle({ idx0, idx1, idx2 });
            chunkGobj.AddTriangle({ idx0, idx2, idx3 });
        }
        tile = getTile(chunk.GetTileInfo(world, x, y, z + 1));
        if (tile == nullptr || !tile->IsFlushZm())
        {
            //Render face Zp
            auto idx0 = chunkGobj.AddVertex({ x,     y,     z + 1 }, { x       / TILES_PER_TEXTURE_U, y       / TILES_PER_TEXTURE_V }, { 0, 0, 1 });
            auto idx1 = chunkGobj.AddVertex({ x + 1, y,     z + 1 }, { (x + 1) / TILES_PER_TEXTURE_U, y       / TILES_PER_TEXTURE_V }, { 0, 0, 1 });
            auto idx2 = chunkGobj.AddVertex({ x + 1, y + 1, z + 1 }, { (x + 1) / TILES_PER_TEXTURE_U, (y + 1) / TILES_PER_TEXTURE_V }, { 0, 0, 1 });
            auto idx3 = chunkGobj.AddVertex({ x,     y + 1, z + 1 }, { x       / TILES_PER_TEXTURE_U, (y + 1) / TILES_PER_TEXTURE_V }, { 0, 0, 1 });

            chunkGobj.AddTriangle({ idx0, idx2, idx1 });
            chunkGobj.AddTriangle({ idx0, idx3, idx2 });
        }
    }
}
