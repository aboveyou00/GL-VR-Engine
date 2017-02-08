#pragma once
#include "BoxBody.h"

namespace GlEngine
{
    class ENGINE_SHARED TileBoxBody : public BoxBody
    {
    public:
        TileBoxBody(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, int tileId);
        ~TileBoxBody();

        virtual std::string name();
        virtual int id() override;
        virtual bool Collide(Body * other, Collision*& out, bool trySwitch = true) override;

        int tileId;
    };
}