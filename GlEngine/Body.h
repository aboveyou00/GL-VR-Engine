#pragma once

namespace GlEngine
{
    class ENGINE_SHARED Body
    {
    public:
        Body();
        ~Body();
        virtual const char *name();
        virtual bool Collide(Body* other, bool trySwitched = true);

        virtual float MinX() = 0;
        virtual float MaxX() = 0;
        virtual float MinY() = 0;
        virtual float MaxY() = 0;
        virtual float MinZ() = 0;
        virtual float MaxZ() = 0;

        bool movable;

        Vector<3> position;
        Vector<3> velocity;
    };
}