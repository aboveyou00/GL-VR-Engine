#pragma once

#include "Body.h"

namespace GlEngine
{
	class RigidBody : public Body
	{
	public:
		RigidBody();
		~RigidBody();

		virtual const char * name();
		virtual bool Collide(Body* other, bool trySwitch = true) override;
	};
}