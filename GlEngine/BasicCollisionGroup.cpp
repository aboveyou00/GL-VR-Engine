#include "stdafx.h"
#include "BasicCollisionGroup.h"
#include "Collision.h"
#include "Body.h"

namespace GlEngine
{
    BasicCollisionGroup::BasicCollisionGroup()
    {
    }
    BasicCollisionGroup::~BasicCollisionGroup()
    {
    }

    void BasicCollisionGroup::Add(Body *body)
    {
        bodies.push_back(body);
    }
    void BasicCollisionGroup::Add(Actor *actor)
    {
        bodies.push_back(actor->body);
    }

    std::vector<Collision*> BasicCollisionGroup::Collide(Body * body)
    {
        std::vector<Collision*> result;
        Collision* col = nullptr;
        for (Body * b : bodies)
            if (b->Collide(body, col))
                result.push_back(col);
        return result;
    }

    std::vector<Collision*> BasicCollisionGroup::Collide(CollisionGroup * other, bool)
    {
        std::vector<Collision*> result;
        for (Body * b : bodies)
        {
            std::vector<Collision*> partial = other->Collide(b);
            result.insert(result.end(), partial.begin(), partial.end());
        }
        return result;
    }

    std::vector<Collision*> BasicCollisionGroup::CollideSelf()
    {
        std::vector<Collision*> result;
        Collision* col = nullptr;
        for (unsigned i = 0; i < bodies.size(); i++)
            for (unsigned j = 0; j < i; j++)
                if (bodies[i]->Collide(bodies[j], col))
                    result.push_back(col);
        return result;
    }
}
