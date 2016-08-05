#include "stdafx.h"
#include "TileCollisionProvider.h"

#include "TileManager.h"
#include "Body.h"
#include "EmptyBody.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "BoxBody.h"

namespace TileRPG
{
	TileCollisionProvider::TileCollisionProvider(World * world)
		: world(world), currentBody(nullptr)
	{
	}
	TileCollisionProvider::~TileCollisionProvider()
	{
		if (currentBody != nullptr)
			delete currentBody;
	}

	GlEngine::Body * TileCollisionProvider::GetBody(int x, int y, int z)
	{
		int tile = world->GetTileInfo(x, y, z);
        auto &tileManager = TileManager::GetInstance();

		if (currentBody != nullptr)
			delete currentBody;

		auto t = tileManager.GetTile(tile);
		if (t != nullptr && t->IsSolid())
		{
			std::cout << " S | ";
    		currentBody = new GlEngine::BoxBody(0, 1, 0, 1, 0, 1);
			currentBody->position = { x, y, z };
			return currentBody;
		}
		else
		{
			std::cout << " E | ";
			currentBody = new GlEngine::EmptyBody();
			return currentBody;
		}
	}
}
