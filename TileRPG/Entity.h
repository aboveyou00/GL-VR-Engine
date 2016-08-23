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
        Entity(GlEngine::Body *body);
        ~Entity();

        GlEngine::Force *gravity() const;

    private:
        GlEngine::Force *_gravity;
    };
}
