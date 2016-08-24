#include "stdafx.h"
#include "RockTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "Texture.h"
#include "BlinnMaterial.h"

//#include "ChunkGraphicsObject.h"
//#include "FbxGraphicsObject.h"
//#include "MathUtils.h"
//#include "Chunk.h"
//#include "World.h"

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

    //void RockTile::AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z)
    //{
    //    static auto none = GlEngine::FbxGraphicsObject::Create("Resources/cave/none.fbx");
    //    static auto a =    GlEngine::FbxGraphicsObject::Create("Resources/cave/a.fbx");
    //    static auto ab =   GlEngine::FbxGraphicsObject::Create("Resources/cave/ab.fbx");
    //    static auto ac =   GlEngine::FbxGraphicsObject::Create("Resources/cave/ac.fbx");
    //    static auto abc =  GlEngine::FbxGraphicsObject::Create("Resources/cave/abc.fbx");
    //    static auto abcd = GlEngine::FbxGraphicsObject::Create("Resources/cave/abcd.fbx");

    //    static auto up_vec = Vector<4> { 0, 1, 0, 0 };

    //    static auto ident = Matrix<4, 4>::Identity();
    //    static auto rot90 = Matrix<4, 4>::TranslateMatrix({ -1, 0, 0 }) * Matrix<4, 4>::YawMatrix((float)90deg);
    //    static auto rot180 = rot90 * rot90;
    //    static auto rot270 = rot180 * rot90;
    //    static struct
    //    {
    //        GlEngine::FbxGraphicsObject *gobj;
    //        Matrix<4, 4> transform;
    //    } selector[] = {
    //        { abcd, ident  }, //0b00001
    //        { abc,  rot90  }, //0b00011
    //        { abc,  rot180 }, //0b00101
    //        { ab,   rot180 }, //0b00111

    //        { abc,  rot270 }, //0b01001
    //        { ac,   rot90  }, //0b01011
    //        { ab,   rot270 }, //0b01101
    //        { a,    rot270 }, //0b01111

    //        { abc,  ident  }, //0b10001
    //        { ab,   rot90  }, //0b10011
    //        { ac,   ident  }, //0b10101
    //        { a,    rot180 }, //0b10111

    //        { ab,   ident  }, //0b11001
    //        { a,    rot90  }, //0b11011
    //        { a,    ident  }, //0b11101
    //        { none, ident  }, //0b11111
    //    };

    //    auto &chunk = chunkGobj.GetChunk();
    //    auto world = &chunkGobj.GetWorld();
    //    ITile *tile;

    //    bool west = false, north = false, east = false, south = false;

    //    tile = getTile(chunk.GetTileInfo(world, x - 1, y, z));
    //    if (tile == nullptr || !tile->IsFlushXp() || !tile->IsSolid()) west = true;

    //    tile = getTile(chunk.GetTileInfo(world, x, y, z + 1));
    //    if (tile == nullptr || !tile->IsFlushZm() || !tile->IsSolid()) north = true;

    //    tile = getTile(chunk.GetTileInfo(world, x + 1, y, z));
    //    if (tile == nullptr || !tile->IsFlushXm() || !tile->IsSolid()) east = true;

    //    tile = getTile(chunk.GetTileInfo(world, x, y, z - 1));
    //    if (tile == nullptr || !tile->IsFlushZp() || !tile->IsSolid()) south = true;

    //    auto idx = (west  ? 0b0001 : 0) |
    //               (north ? 0b0010 : 0) |
    //               (east  ? 0b0100 : 0) |
    //               (south ? 0b1000 : 0);

    //    auto selection = selector[idx];
    //    if (selection.gobj != nullptr)
    //    {
    //        auto translate = Matrix<4, 4>::TranslateMatrix((float)x, (float)y, (float)z);
    //        chunkGobj.AddInstance(selection.gobj, selection.transform * translate);
    //    }
    //}

    const char *RockTile::footstep_sound()
    {
        return "footstep-rock.ogg";
    }
}
