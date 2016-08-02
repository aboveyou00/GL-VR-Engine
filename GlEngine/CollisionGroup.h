#pragma once

namespace GlEngine
{
	class Body;

	class CollisionGroup
	{
	public:
		CollisionGroup();
		~CollisionGroup();

		virtual void Collide(Body * actor) = 0;
		virtual void Collide(CollisionGroup * other) = 0;
	};
}