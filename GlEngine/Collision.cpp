#include "stdafx.h"
#include "Collision.h"
#include "Body.h"

namespace GlEngine
{
    Collision::Collision(Body* bodyA, Body* bodyB)
        : bodyA(bodyA), bodyB(bodyB), bodyAExists(true), bodyBExists(true)
    {
        bodyA->currentCollisions.insert(this);
        bodyB->currentCollisions.insert(this);
    }
    Collision::~Collision()
    {
        if (bodyAExists)
            bodyA->currentCollisions.erase(this);
        if (bodyBExists)
            bodyB->currentCollisions.erase(this);
    }
    int Collision::id()
    {
        return 0;
    }
}