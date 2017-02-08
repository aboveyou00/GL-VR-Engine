#include "stdafx.h"
#include "Space.h"

namespace GlEngine
{
    Space::Space()
        : defaultGroup(new BasicCollisionGroup()), currentCollisions(std::vector<Collision*>())
    {
        collisionGroups.push_back(defaultGroup);
        for (int i = 0; i < maxElement; i++)
            elements[i] = nullptr;
    }
    Space::~Space()
    {
        SafeDelete(defaultGroup);
    }

    bool Space::Initialize()
    {
        return true;
    }
    void Space::Shutdown()
    {
    }

    std::string Space::name()
    {
        return "Space";
    }
    
    void Space::Tick(float delta)
    {
        for (int i = 0; i < maxElement; i++)
            if (elements[i] != nullptr)
                elements[i]->Tick(delta);
        ManageCollisions();
    }

    void Space::Add(GameObject * gameObject)
    {
        Add(gameObject->actor());
    }

    void Space::Add(Actor * actor)
    {
        elements[nextEmptyActor] = actor;
        while (elements[++nextEmptyActor] != nullptr) ;
        defaultGroup->Add(actor);
    }

    void Space::Add(CollisionGroup * collisionGroup)
    {
        collisionGroups.push_back(collisionGroup);
    }

    std::vector<Collision*> Space::ManageCollisions()
    {
        for (Collision* col : currentCollisions)
            delete col;
        currentCollisions.clear();
        for (unsigned i = 0; i < collisionGroups.size(); i++)
        {
            for (unsigned j = i + 1; j < collisionGroups.size(); j++)
            {
                std::vector<Collision*> partial = collisionGroups[i]->Collide(collisionGroups[j]);
                currentCollisions.insert(currentCollisions.end(), partial.begin(), partial.end());
            }
        }
        for (CollisionGroup* collisionGroup : collisionGroups)
        {
            std::vector<Collision*> partial = collisionGroup->CollideSelf();
            currentCollisions.insert(currentCollisions.end(), partial.begin(), partial.end());
        }
        return currentCollisions;
    }
}
