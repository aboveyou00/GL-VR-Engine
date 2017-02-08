#pragma once

#include "RigidBody.h"

namespace GlEngine
{
    class ENGINE_SHARED BoxBody : public RigidBody
    {
    public:
        BoxBody(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
        ~BoxBody();

        float minX, maxX, minY, maxY, minZ, maxZ;

        virtual std::string name() override;
        virtual int id() override;

        virtual bool Collide(Body * other, Collision*& out, bool trySwitch = true) override;

        virtual float MinX() override;
        virtual float MaxX() override;
        virtual float MinY() override;
        virtual float MaxY() override;
        virtual float MinZ() override;
        virtual float MaxZ() override;

    private:
        static void BacktrackSingle(Body * first, Body * second, Collision *& out); // Backtracks the second argument
        static void Backtrack(Body * first, Body * second, Collision *& out);
    };
}