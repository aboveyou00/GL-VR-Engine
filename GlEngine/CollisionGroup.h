#pragma once

namespace GlEngine
{
    class Body;
    class Collision;

    class ENGINE_SHARED CollisionGroup
    {
    public:
        CollisionGroup();
        ~CollisionGroup();

        virtual std::vector<Collision*> Collide(Body *body) = 0;
        virtual std::vector<Collision*> Collide(CollisionGroup *other, bool trySwitch = true) = 0;
        virtual std::vector<Collision*> CollideSelf() = 0;
    };
}