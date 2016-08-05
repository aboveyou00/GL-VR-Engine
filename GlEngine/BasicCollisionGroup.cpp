#include "stdafx.h"
#include "BasicCollisionGroup.h"

namespace GlEngine
{
	BasicCollisionGroup::BasicCollisionGroup()
	{
	}
	BasicCollisionGroup::~BasicCollisionGroup()
	{
	}

	void BasicCollisionGroup::Add(Body * body)
	{
		bodies.push_back(body);
	}
	void BasicCollisionGroup::Add(Actor * actor)
	{
		bodies.push_back(actor->body);
	}

	void BasicCollisionGroup::Collide(Body * body)
	{
		for (Body * b : bodies)
		{
			b->Collide(body);
		}
	}

	void BasicCollisionGroup::Collide(CollisionGroup * other, bool)
	{
		for (Body * b : bodies)
			other->Collide(b);
	}
}