#include "stdafx.h"
#include "RockTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "Shader.h"
#include "Texture.h"

namespace TileRPG
{
    RockTile::RockTile()
        : ITile(0x11, true, true)
    {
    }
    RockTile::~RockTile()
    {
    }

    SINGLETON_TILE_CPP(RockTile);

    void RockTile::AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z)
    {
        static auto shader = GlEngine::Shader::Create("Shaders", "direct_light_tex");
        static auto texture = GlEngine::Texture::FromFile("Textures/green.png");
        chunkGobj.SetGraphics(shader, texture);
        ITile::AddToChunkGraphicsObject(chunkGobj, x, y, z);
    }
}
