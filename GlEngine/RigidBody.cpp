#include "stdafx.h"
#include "RigidBody.h"

namespace GlEngine
{
	RigidBody::RigidBody()
	{
	}
	RigidBody::~RigidBody()
	{
	}

	const char * RigidBody::name()
	{
		return "RigidBody";
	}

	bool RigidBody::Collide(Body* other, bool trySwitch)
	{
		//if (strcmp(other->name(), "RigidBody"))
		//{

		//}
		return Body::Collide(other, trySwitch);
	}
}