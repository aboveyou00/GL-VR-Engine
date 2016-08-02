#include "stdafx.h"
#include "Space.h"

namespace GlEngine
{
	Space::Space()
	{
	}
	Space::~Space()
	{
	}

	bool Space::Initialize()
	{
		return true;
	}
	void Space::Shutdown()
	{
	}

	const char *Space::name()
	{
		return "Space";
	}
	
	void Space::Tick(float delta)
	{
		for (int i = 0; i < maxElement; i++)
			elements[i]->Tick(delta);
		ManageCollisions();
	}

	void Space::Add(Actor * actor)
	{
		elements[nextEmptyActor] = actor;
		while (!elements[++nextEmptyActor]->active);
	}

	void Space::ManageCollisions()
	{
		for (int i = 0; i < maxElement; i++)
		{
			if (!elements[i]->active || strcmp(elements[i]->body->name(), "EmptyBody") == 0)
				continue;
			
		}
	}
}