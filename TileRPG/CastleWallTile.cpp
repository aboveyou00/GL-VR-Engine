#include "stdafx.h"
#include "CastleWallTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "FbxGraphicsObject.h"
#include "MathUtils.h"
#include "Chunk.h"
#include "World.h"
#include "IStairsTile.h"

#include "SolidAirTile.h"

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
        static auto none_notop = GlEngine::FbxGraphicsObject::Create("Resources/castle/none_notop.fbx"s);
        static auto none_top =   GlEngine::FbxGraphicsObject::Create("Resources/castle/none_top.fbx"s);
        static auto a_notop =    GlEngine::FbxGraphicsObject::Create("Resources/castle/a_notop.fbx"s);
        static auto a_top =      GlEngine::FbxGraphicsObject::Create("Resources/castle/a_top.fbx"s);
        static auto ab_notop =   GlEngine::FbxGraphicsObject::Create("Resources/castle/ab_notop.fbx"s);
        static auto ab_top =     GlEngine::FbxGraphicsObject::Create("Resources/castle/ab_top.fbx"s);
        static auto ac_notop =   GlEngine::FbxGraphicsObject::Create("Resources/castle/ac_notop.fbx"s);
        static auto ac_top =     GlEngine::FbxGraphicsObject::Create("Resources/castle/ac_top.fbx"s);
        static auto abc_notop =  GlEngine::FbxGraphicsObject::Create("Resources/castle/abc_notop.fbx"s);
        static auto abc_top =    GlEngine::FbxGraphicsObject::Create("Resources/castle/abc_top.fbx"s);
        static auto abcd_top =   GlEngine::FbxGraphicsObject::Create("Resources/castle/abcd_top.fbx"s);

        static auto up_vec = Vector<4> { 0, 1, 0, 0 };
        static auto ident = Matrix<4, 4>::Identity();
        static auto rot90 = Matrix<4, 4>::TranslateMatrix({ -1, 0, 0 }) * Matrix<4, 4>::YawMatrix((float)90deg);
        static auto rot180 = rot90 * rot90;
        static auto rot270 = rot180 * rot90;
        static struct
        {
            GlEngine::FbxGraphicsObject *gobj;
            Matrix<4, 4> transform;
        } selector[] = {
            { nullptr,    ident  }, //0b00000
            { abcd_top,   ident  }, //0b00001
            { abc_notop,  rot90  }, //0b00010
            { abc_top,    rot90  }, //0b00011
            { abc_notop,  rot180 }, //0b00100
            { abc_top,    rot180 }, //0b00101
            { ab_notop,   rot180 }, //0b00110
            { ab_top,     rot180 }, //0b00111

            { abc_notop,  rot270 }, //0b01000
            { abc_top,    rot270 }, //0b01001
            { ac_notop,   rot90  }, //0b01010
            { ac_top,     rot90  }, //0b01011
            { ab_notop,   rot270 }, //0b01100
            { ab_top,     rot270 }, //0b01101
            { a_notop,    rot270 }, //0b01110
            { a_top,      rot270 }, //0b01111
            
            { abc_notop,  ident  }, //0b10000
            { abc_top,    ident  }, //0b10001
            { ab_notop,   rot90  }, //0b10010
            { ab_top,     rot90  }, //0b10011
            { ac_notop,   ident  }, //0b10100
            { ac_top,     ident  }, //0b10101
            { a_notop,    rot180 }, //0b10110
            { a_top,      rot180 }, //0b10111

            { ab_notop,   ident  }, //0b11000
            { ab_top,     ident  }, //0b11001
            { a_notop,    rot90  }, //0b11010
            { a_top,      rot90  }, //0b11011
            { a_notop,    ident  }, //0b11100
            { a_top,      ident  }, //0b11101
            { none_notop, ident  }, //0b11110
            { none_top,   ident  }, //0b11111
        };
        
        auto &chunk = chunkGobj.GetChunk();
        auto world = &chunkGobj.GetWorld();
        ITile *tile;

        tile = getTile(chunk.GetTileInfo(world, x, y + 1, z));
        bool hasTop = tile == nullptr || !tile->IsFlushYm() || !tile->IsSolid();

        bool west = false, north = false, east = false, south = false;

        tile = getTile(chunk.GetTileInfo(world, x - 1, y + 1, z));
        if (tile == nullptr || !tile->IsFlushXp() || !tile->IsSolid())
        {
            tile = getTile(chunk.GetTileInfo(world, x - 1, y, z));
            if (tile == nullptr || !tile->IsFlushYp() || !tile->IsSolid()) west = true; //TODO: Check for stairs as an exception
        }

        tile = getTile(chunk.GetTileInfo(world, x, y + 1, z + 1));
        if (tile == nullptr || !tile->IsFlushZm() || !tile->IsSolid())
        {
            tile = getTile(chunk.GetTileInfo(world, x, y, z + 1));
            if (tile == nullptr || !tile->IsFlushYp() || !tile->IsSolid()) north = true; //TODO: Check for stairs as an exception
        }

        tile = getTile(chunk.GetTileInfo(world, x + 1, y + 1, z));
        if (tile == nullptr || !tile->IsFlushXm() || !tile->IsSolid())
        {
            tile = getTile(chunk.GetTileInfo(world, x + 1, y, z));
            if (tile == nullptr || !tile->IsFlushYp() || !tile->IsSolid())
            {
                auto stairs = dynamic_cast<IStairsTile*>(tile);
                if (stairs == nullptr) east = true; //TODO: Check for the correct orientation
            }
        }

        tile = getTile(chunk.GetTileInfo(world, x, y + 1, z - 1));
        if (tile == nullptr || !tile->IsFlushZp() || !tile->IsSolid())
        {
            tile = getTile(chunk.GetTileInfo(world, x, y, z - 1));
            if (tile == nullptr || !tile->IsFlushYp() || !tile->IsSolid()) south = true; //TODO: Check for stairs as an exception
        }

        auto idx = (hasTop ? 0b00001 : 0) |
                   (west   ? 0b00010 : 0) |
                   (north  ? 0b00100 : 0) |
                   (east   ? 0b01000 : 0) |
                   (south  ? 0b10000 : 0);

        auto selection = selector[idx];
        if (selection.gobj != nullptr)
        {
            auto translate = Matrix<4, 4>::TranslateMatrix((float)x, (float)y, (float)z);
            chunkGobj.AddInstance(selection.gobj, selection.transform * translate);
        }
    }
}
