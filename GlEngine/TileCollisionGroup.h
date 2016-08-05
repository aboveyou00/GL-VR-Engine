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

		virtual void Collide(Body * body) override
		{
			int minX = Util::floor_int(body->MinX());
			int maxX = Util::ceil_int(body->MaxX());
			int minY = Util::floor_int(body->MinY());
			int maxY = Util::ceil_int(body->MaxY());
			int minZ = Util::floor_int(body->MinZ());
			int maxZ = Util::ceil_int(body->MaxZ());

			for (int x = minX; x < maxX; x++)
				for (int y = minY; y < maxY; y++)
					for (int z = minZ; z < maxZ; z++)
					{
						std::cout << x << "," << y << "," << z << " | ";
						body->Collide(provider->GetBody(x, y, z));
					}
			std::cout << std::endl;
		}

		virtual void Collide(CollisionGroup * other, bool trySwitch = true) override
		{
			if (trySwitch)
				other->Collide(this, false);
			else
				return;
		}

	private:
		TileProviderT * provider;
	};
}