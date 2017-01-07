#pragma once

#include "CollisionGroup.h"
#include <vector>
#include "Actor.h"

namespace GlEngine
{
    class ENGINE_SHARED BasicCollisionGroup : public CollisionGroup
    {
    public:
        BasicCollisionGroup();
        ~BasicCollisionGroup();

        void Add(Body *body);
        void Add(Actor *actor);

        virtual std::vector<Collision*> Collide(Body *body) override;
        virtual std::vector<Collision*> Collide(CollisionGroup *other, bool trySwitch = true) override;
        virtual std::vector<Collision*> CollideSelf();

    private:
        std::vector<Body*> bodies;
    };
}