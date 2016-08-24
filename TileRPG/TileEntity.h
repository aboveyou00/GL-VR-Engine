#pragma once

#include "GameObject.h"

namespace TileRPG
{
    class TileEntity : public GlEngine::GameObject
    {
    public:
        TileEntity(Vector<3> position = { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        ~TileEntity();


    };
}
