#include "stdafx.h"
#include "TileBoxBody.h"
#include "TileCollision.h"

namespace GlEngine
{
    TileBoxBody::TileBoxBody(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, int tileId)
        : BoxBody(minX, maxX, minY, maxY, minZ, maxZ), tileId(tileId)
    {
    }

    TileBoxBody::~TileBoxBody()
    {
    }
    const char * TileBoxBody::name()
    {
        return "TileBoxBody";
    }
    int TileBoxBody::id()
    {
        return 2;
    }
    bool TileBoxBody::Collide(Body * other, Collision *& out, bool trySwitch)
    {
        Collision * col = nullptr;
        bool result = BoxBody::Collide(other, col, trySwitch);
        if (result)
        {
            auto bcol = (BoxCollision*)col;
            out = new TileCollision(bcol->bodyA, bcol->bodyB, bcol->side, tileId);
            delete col;
        }
        return result;
    }
}