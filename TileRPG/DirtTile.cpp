#include "stdafx.h"
#include "DirtTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "Texture.h"
#include "PhongMaterial.h"

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
        auto texture = GlEngine::Texture::FromFile("Textures/sand.png"s);
        auto mat = new GlEngine::PhongMaterial(texture);
        chunkGobj.SetMaterial(mat);
        ITile::AddToChunkGraphicsObject(chunkGobj, x, y, z);
    }
}
