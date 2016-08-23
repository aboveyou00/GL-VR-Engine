#include "stdafx.h"
#include "Space.h"

namespace GlEngine
{
	Space::Space()
	{
		defaultGroup = new BasicCollisionGroup();
		collisionGroups.push_back(defaultGroup);
		for (int i = 0; i < maxElement; i++)
			elements[i] = nullptr;
	}
	Space::~Space()
	{
		delete defaultGroup;
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
			if (elements[i] != nullptr)
				elements[i]->Tick(delta);
		ManageCollisions();
	}

	void Space::Add(GameObject * gameObject)
	{
		Add(gameObject->actor());
	}

	void Space::Add(Actor * actor)
	{
		elements[nextEmptyActor] = actor;
		while (elements[++nextEmptyActor] != nullptr) ;
		defaultGroup->Add(actor);
	}

	void Space::Add(CollisionGroup * collisionGroup)
	{
		collisionGroups.push_back(collisionGroup);
	}

	void Space::ManageCollisions()
	{
		for (unsigned i = 0; i < collisionGroups.size(); i++)
			for (unsigned j = i+1; j < collisionGroups.size(); j++)
				collisionGroups[i]->Collide(collisionGroups[j]);
	}
}