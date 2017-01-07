#include "stdafx.h"
#include "TileEntity.h"

#include "BoxBody.h"

namespace TileRPG
{
    TileEntity::TileEntity(Vector<3, unsigned> size, Vector<3> position, Matrix<4, 4> orientation)
        : GameObject(position, orientation)
    {
        auto &act_body = actor()->body;
        act_body = new GlEngine::BoxBody(0, 0, 0, (float)size[0], (float)size[1], (float)size[2]);
        act_body->movable = false;
        act_body->position = position;
        RequireTick();
    }
    TileEntity::~TileEntity()
    {
    }
}
