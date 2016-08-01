#pragma once

#include "GameObject.h"

namespace TileRPG
{
	class World;
	class WorldLoader;

	class PlayerObject : public GlEngine::GameObject
	{
	public:
		PlayerObject(World *world);
		~PlayerObject();
		
		void Tick(float delta) override;

		const char *name() override;

		void HandleEvent(GlEngine::Events::Event &evt) override;

		GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;
	
	private:
		
		WorldLoader* loader;
		float timePassed;
		float direction = 0;
		bool leftPressed, rightPressed, upPressed, downPressed, inPressed, outPressed;
	};
}