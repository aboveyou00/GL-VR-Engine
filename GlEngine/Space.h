#pragma once

#include "IComponent.h"
#include "EngineShared.h"
#include "Actor.h"
#include "Octree.h"
#include "CollisionGroup.h"
#include "BasicCollisionGroup.h"
#include "GameObject.h"

namespace GlEngine
{
    class ENGINE_SHARED Space : public IComponent
    {
    public:
        Space();
        ~Space();

        bool Initialize() override;
        void Shutdown() override;

        const char *name() override;

        void Tick(float delta);

        static const int maxElement = 2048;
        Actor * elements[maxElement];
        int nextEmptyActor = 0;

        BasicCollisionGroup * defaultGroup;

        std::vector<CollisionGroup*> collisionGroups;

        void Add(GameObject * gameObject);
        void Add(Actor * actor);
        void Add(CollisionGroup * collisionGroup);
        std::vector<Collision*> ManageCollisions();

    private:
        std::vector<Collision*> currentCollisions;
    };
}