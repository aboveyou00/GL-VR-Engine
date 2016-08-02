#pragma once

#include "CollisionGroup.h"
#include "Body.h"

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
			int minX = (int)body->MinX();
			int maxX = (int)(body->MaxX() + 1);
			int minY = (int)body->MinY();
			int maxY = (int)(body->MaxY() + 1);
			int minZ = (int)body->MinZ();
			int maxZ = (int)(body->MaxZ() + 1);

			for (int x = minX; x < maxX; x++)
				for (int y = minY; y < maxY; y++)
					for (int z = minZ; z < maxZ; z++)
						body->Collide(provider->GetBody(x, y, z));
		}
		virtual void Collide(CollisionGroup * other) override
		{
			int minX = (int)body->MinX();
			int maxX = (int)(body->MaxX() + 1);
			int minY = (int)body->MinY();
			int maxY = (int)(body->MaxY() + 1);
			int minZ = (int)body->MinZ();
			int maxZ = (int)(body->MaxZ() + 1);

			for (int x = minX; x < maxX; x++)
				for (int y = minY; y < maxY; y++)
					for (int z = minZ; z < maxZ; z++)
						other->Collide(provider->GetBody(x, y, z));
		}

	private:
		TileProviderT * provider;
	};
}