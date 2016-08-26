#pragma once

#include "CompoundGraphicsObject.h"

namespace TileRPG
{
    class CompassGraphicsObject : public GlEngine::CompoundGraphicsObject<2>
    {
    public:
        CompassGraphicsObject();
        ~CompassGraphicsObject();

        void SetRotation(float rot);

    private:
        float rot;
    };
}
