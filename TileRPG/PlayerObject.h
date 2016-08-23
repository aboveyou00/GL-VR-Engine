#pragma once

#include "Entity.h"

namespace GlEngine
{
    class IAudioSource;
	class Force;
}

namespace TileRPG
{
	class World;
	class WorldLoader;

	class PlayerObject : public Entity
	{
	public:
		PlayerObject(World *world);
		~PlayerObject();
		
        bool Initialize() override;
		void Tick(float delta) override;
		void Jump();

		const char *name() override;

		void HandleEvent(GlEngine::Events::Event &evt) override;

		GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

	private:
		GlEngine::IAudioSource *footsteps;
		
		WorldLoader* loader;
		float direction = 0;
		bool leftPressed, rightPressed, upPressed, downPressed, inPressed, outPressed;
	};
}
