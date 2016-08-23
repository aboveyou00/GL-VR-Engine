#include "stdafx.h"
#include "Entity.h"

#include "Body.h"
#include "Force.h"

namespace TileRPG
{
    Entity::Entity(GlEngine::Body *body)
    {
        actor()->body = body;
        actor()->body->movable = true;
        _gravity = new GlEngine::Force({ 0, -9.8f, 0 });
        actor()->AddForce(_gravity);
    }
    Entity::~Entity()
    {
        SafeDelete(actor()->body);
        SafeDelete(_gravity);
    }
    GlEngine::Force *Entity::gravity() const
    {
        return _gravity;
    }
}
