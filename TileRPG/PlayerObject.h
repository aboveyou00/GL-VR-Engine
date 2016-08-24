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
		PlayerObject(World *world, Vector<3> position = { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
		~PlayerObject();
		
        bool Initialize() override;
		void Tick(float delta) override;
        void Shutdown() override;

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
