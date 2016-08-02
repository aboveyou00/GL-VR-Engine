#pragma once

#include "CollisionGroup.h"
#include <vector>
#include "Actor.h"

namespace GlEngine
{
	class BasicCollisionGroup : public CollisionGroup
	{
	public:
		BasicCollisionGroup();
		~BasicCollisionGroup();

		void Add(Body * body);
		void Add(Actor *  actor);

		virtual void Collide(Body * body) override;
		virtual void Collide(CollisionGroup * other) override;

	private:
		std::vector<Body*> bodies;
	};
}