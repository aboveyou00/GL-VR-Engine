#include "stdafx.h"
#include "Actor.h"
#include "Force.h"
#include "EmptyBody.h"

namespace GlEngine
{
    Actor::Actor()
        : active(false), body(new EmptyBody())
    {
    }
    Actor::~Actor()
    {
        delete body;
    }

    void Actor::Tick(float delta)
    {
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
}