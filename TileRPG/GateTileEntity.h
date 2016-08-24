#pragma once

#include "TileEntity.h"

namespace TileRPG
{
    class GateTileEntity : public TileEntity
    {
    public:
        GateTileEntity(Vector<3> position = { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        ~GateTileEntity();

        const char *name() override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext&) override;
    };
}
