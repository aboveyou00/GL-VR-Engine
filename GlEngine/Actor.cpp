#include "stdafx.h"
#include "Actor.h"
#include "Force.h"
#include "EmptyBody.h"

namespace GlEngine
{
	Actor::Actor()
		: active(false), body(EmptyBody())
	{
	}
	Actor::~Actor()
	{
	}

	void Actor::Tick(float delta)
	{
		Vector<3> totalForce;
		for (int i = 0; i < numForces; i++)
			totalForce += forces[i]->component;
		
		position += 0.5 * totalForce * delta * delta;
		velocity += totalForce * delta;
	}

	void Actor::AddForce(Force* force)
	{
		forces[numForces++] = force;
	}
}