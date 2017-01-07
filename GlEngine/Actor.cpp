#include "stdafx.h"
#include "Actor.h"
#include "Force.h"
#include "EmptyBody.h"

namespace GlEngine
{
    Actor::Actor()
        : _active(true), body(new EmptyBody())
    {
    }
    Actor::~Actor()
    {
        SafeDelete(body);
    }

    void Actor::Tick(float delta)
    {
        if (!active()) return;

        if (!body->movable)
            return;
        
        Vector<3> totalForce;
        for (int i = 0; i < numForces; i++)
            totalForce += forces[i]->component;
    
        body->position += 0.5 * totalForce * delta * delta + body->velocity * delta;
        body->velocity += totalForce * delta;
    }

    void Actor::AddForce(Force* force)
    {
        forces[numForces++] = force;
    }

    void Actor::Activate()
    {
        _active = true;
    }
    void Actor::Deactivate()
    {
        _active = false;
    }
    bool Actor::active() const
    {
        return _active;
    }
}