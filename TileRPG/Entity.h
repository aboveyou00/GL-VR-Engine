#pragma once

#include "GameObject.h"

namespace GlEngine
{
    class Body;
    class Force;
}

namespace TileRPG
{
    class Entity : public GlEngine::GameObject
    {
    public:
        Entity(GlEngine::Body *body, Vector<3> position = { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        ~Entity();

        GlEngine::Force *gravity() const;

    private:
        GlEngine::Force *_gravity;
    };
}
