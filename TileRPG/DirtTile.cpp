#include "stdafx.h"
#include "DirtTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "Shader.h"
#include "Texture.h"

namespace TileRPG
{
    DirtTile::DirtTile()
        : ITile(0x10, true, true)
    {
    }
    DirtTile::~DirtTile()
    {
    }

    SINGLETON_TILE_CPP(DirtTile);

    void DirtTile::AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z)
    {
        static auto shader = GlEngine::Shader::Create("Shaders", "direct_light_tex");
        static auto texture = GlEngine::Texture::FromFile("Textures/blue.png");
        chunkGobj.SetGraphics(shader, texture);
        ITile::AddToChunkGraphicsObject(chunkGobj, x, y, z);
    }
}
