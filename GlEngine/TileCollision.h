#pragma once
#include "BoxCollision.h"

namespace GlEngine
{
    class ENGINE_SHARED TileCollision : public BoxCollision
    {
    public:
        TileCollision(Body* bodyA, Body* bodyB, unsigned side, int tileId);
        ~TileCollision();

        virtual int id() override;

        int tileId;
    };
}