#pragma once
#include "Collision.h"
#include <set>

namespace GlEngine
{
    class ENGINE_SHARED Body
    {
    public:
        Body();
        ~Body();
        virtual const char *name();
        virtual int id() = 0;
        virtual bool Collide(Body* other, Collision*& out, bool trySwitched = true);

        virtual float MinX() = 0;
        virtual float MaxX() = 0;
        virtual float MinY() = 0;
        virtual float MaxY() = 0;
        virtual float MinZ() = 0;
        virtual float MaxZ() = 0;

        std::set<Collision*> currentCollisions;

        bool movable;

        Vector<3> position;
        Vector<3> velocity;
    };
}
