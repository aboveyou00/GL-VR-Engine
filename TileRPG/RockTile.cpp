#include "stdafx.h"
#include "RockTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "Texture.h"
#include "BlinnMaterial.h"

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
        auto texture = GlEngine::Texture::FromFile("Textures/rock.png");
        auto mat = GlEngine::BlinnMaterial::Create(texture);
        chunkGobj.SetMaterial(mat);
        ITile::AddToChunkGraphicsObject(chunkGobj, x, y, z);
    }
}
