#include "stdafx.h"
#include "Body.h"

namespace GlEngine
{
    Body::Body()
        : movable(false), currentCollisions(std::set<Collision*>())
    {
    }
    Body::~Body()
    {
        for (Collision* col : currentCollisions)
        {
            if (this == col->bodyA)
                col->bodyAExists = false;
            else
                col->bodyBExists = false;
        }
    }
    const char * Body::name()
    {
        return nullptr;
    }
    bool Body::Collide(Body* other, Collision*& out, bool trySwitched)
    {
        if (trySwitched)
        {
            return other->Collide(this, out, false);
        }
        return false;
    }
}