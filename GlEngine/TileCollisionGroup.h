#pragma once

#include "CollisionGroup.h"
#include "Body.h"
#include "EngineShared.h"
#include "MathUtils.h"

namespace GlEngine
{
    template <typename TileProviderT>
    class TileCollisionGroup : public CollisionGroup
    {
    public:
        TileCollisionGroup(TileProviderT * provider)
            : provider(provider) {}
        ~TileCollisionGroup() {}

        virtual std::vector<Collision*> Collide(Body * body) override
        {
            int minX = Util::floor_int(body->MinX());
            int maxX = Util::ceil_int(body->MaxX());
            int minY = Util::floor_int(body->MinY());
            int maxY = Util::ceil_int(body->MaxY());
            int minZ = Util::floor_int(body->MinZ());
            int maxZ = Util::ceil_int(body->MaxZ());

            std::vector<Collision*> result;
            Collision* col = nullptr;
            for (int x = minX; x < maxX; x++)
                for (int y = minY; y < maxY; y++)
                    for (int z = minZ; z < maxZ; z++)
                        if (body->Collide(provider->GetBody(x, y, z), col))
                            result.push_back(col);
            return result;
        }

        virtual std::vector<Collision*> Collide(CollisionGroup * other, bool trySwitch = true) override
        {
            std::vector<Collision*> result;
            if (trySwitch)
            {
                std::vector<Collision*> partial = other->Collide(this, false);
                result.insert(result.end(), partial.begin(), partial.end());
            }
            return result;
        }

        virtual std::vector<Collision*> CollideSelf() override
        {
            return std::vector<Collision*>();
        }

    private:
        TileProviderT * provider;
    };
}