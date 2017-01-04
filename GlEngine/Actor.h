#pragma once

#include "Body.h"

namespace GlEngine
{
    class Force;

    class ENGINE_SHARED Actor
    {
    public:
        Actor();
        ~Actor();

        bool active;

        Body * body;

        static const int maxForces = 16;
        Force* forces[maxForces];
        int numForces = 0;

        void Tick(float delta);
        void AddForce(Force* force);
    };
}