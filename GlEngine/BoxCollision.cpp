#include "stdafx.h"
#include "BoxCollision.h"

namespace GlEngine
{
	BoxCollision::BoxCollision(Body * bodyA, Body * bodyB, unsigned side)
		: Collision(bodyA, bodyB), side(side)
	{
	}

	BoxCollision::~BoxCollision()
	{
	}
	int BoxCollision::id()
	{
		return 1;
	}
}