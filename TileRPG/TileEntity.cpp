#include "stdafx.h"
#include "TileEntity.h"

namespace TileRPG
{
    TileEntity::TileEntity(Vector<3> position, Matrix<4, 4> orientation)
        : GameObject(position, orientation)
    {
    }
    TileEntity::~TileEntity()
    {
    }


}
