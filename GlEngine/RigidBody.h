#pragma once

#include "Body.h"

namespace GlEngine
{
    class ENGINE_SHARED RigidBody : public Body
    {
    public:
        RigidBody();
        ~RigidBody();

        virtual std::string name() = 0;
        virtual int id() override = 0;
        virtual bool Collide(Body* other, Collision*& out, bool trySwitch = true) override = 0;

        virtual float MinX() override = 0;
        virtual float MaxX() override = 0;
        virtual float MinY() override = 0;
        virtual float MaxY() override = 0;
        virtual float MinZ() override = 0;
        virtual float MaxZ() override = 0;
    };
}
