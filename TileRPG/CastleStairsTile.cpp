#include "stdafx.h"
#include "CastleStairsTile.h"
#include "TileManager.h"

#include "ChunkGraphicsObject.h"
#include "FbxGraphicsObject.h"
#include "MathUtils.h"

namespace TileRPG
{
    CastleStairsTile::CastleStairsTile()
        : IStairsTile(0x19)
    {
    }
    CastleStairsTile::~CastleStairsTile()
    {
    }

    SINGLETON_TILE_CPP(CastleStairsTile);

    void CastleStairsTile::AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z)
    {
        static auto stairs = GlEngine::FbxGraphicsObject::Create("Resources/castle/stairs.fbx");

        static auto up_vec = Vector<4> { 0, 1, 0, 0 };
        static auto ident = Matrix<4, 4>::Identity();
        static auto rot90 = Matrix<4, 4>::TranslateMatrix({ -1, 0, 0 }) * Matrix<4, 4>::YawMatrix((float)90deg);
        static auto rot180 = rot90 * rot90;
        static auto rot270 = rot180 * rot90;

        auto translate = Matrix<4, 4>::TranslateMatrix((float)x, (float)y, (float)z);
        chunkGobj.AddInstance(stairs, ident * translate);
    }
}
