#include "stdafx.h"
#include "DirtTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "Texture.h"
#include "BlinnMaterial.h"

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
        auto texture = GlEngine::Texture::FromFile("Textures/sand.png");
        auto mat = GlEngine::BlinnMaterial::Create(texture);
        chunkGobj.SetMaterial(mat);
        ITile::AddToChunkGraphicsObject(chunkGobj, x, y, z);
    }
}
