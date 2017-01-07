#pragma once

#include "Entity.h"

namespace TileRPG
{
    class GateGuard : public Entity
    {
    public:
        GateGuard(Vector<3> position = { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        ~GateGuard();
        
        const char *name() override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext&) override;
    };
}
