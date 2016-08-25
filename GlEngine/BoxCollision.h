#pragma once
#include "Collision.h"

namespace GlEngine
{
	class ENGINE_SHARED BoxCollision : public Collision
	{
	public:
		BoxCollision(Body* bodyA, Body* bodyB, unsigned side);
		~BoxCollision();

		virtual int id() override;

		unsigned side;
	};
}