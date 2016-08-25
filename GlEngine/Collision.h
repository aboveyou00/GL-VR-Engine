#pragma once

namespace GlEngine
{
	class Body;

	class ENGINE_SHARED Collision
	{
	public:
		Collision(Body* bodyA, Body* bodyB);
		~Collision();

		virtual int id();

		Body* bodyA;
		Body* bodyB;
		bool bodyAExists;
		bool bodyBExists;
	};
}