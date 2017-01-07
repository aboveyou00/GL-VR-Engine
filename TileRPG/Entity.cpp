#include "stdafx.h"
#include "Entity.h"

#include "Body.h"
#include "Force.h"

namespace TileRPG
{
    Entity::Entity(GlEngine::Body *body, Vector<3> position, Matrix<4, 4> orientation)
        : GameObject(position, orientation)
    {
        auto &act_body = actor()->body;
        act_body = body;
        act_body->movable = true;
        act_body->position = position;
        _gravity = new GlEngine::Force({ 0, -9.8f, 0 });
        actor()->AddForce(_gravity);
        RequireTick();
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
