#pragma once

#include "Body.h"

namespace GlEngine
{
    class ENGINE_SHARED EmptyBody : public Body
    {
    public:
        EmptyBody();
        ~EmptyBody();

        virtual const char *name() override;
        virtual bool Collide(Body* other, bool trySwitched = true) override;

        virtual float MinX() override;
        virtual float MaxX() override;
        virtual float MinY() override;
        virtual float MaxY() override;
        virtual float MinZ() override;
        virtual float MaxZ() override;
    };
}