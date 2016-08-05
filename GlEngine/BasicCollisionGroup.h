#pragma once

#include "CollisionGroup.h"
#include <vector>
#include "Actor.h"

namespace GlEngine
{
	class ENGINE_SHARED BasicCollisionGroup : public CollisionGroup
	{
	public:
		BasicCollisionGroup();
		~BasicCollisionGroup();

		void Add(Body * body);
		void Add(Actor *  actor);

		virtual void Collide(Body * body) override;
		virtual void Collide(CollisionGroup * other, bool trySwitch = true) override;

	private:
		std::vector<Body*> bodies;
	};
}