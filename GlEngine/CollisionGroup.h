#pragma once

namespace GlEngine
{
	class Body;

	class ENGINE_SHARED CollisionGroup
	{
	public:
		CollisionGroup();
		~CollisionGroup();

		virtual void Collide(Body * actor) = 0;
		virtual void Collide(CollisionGroup * other, bool trySwitch = true) = 0;
	};
}