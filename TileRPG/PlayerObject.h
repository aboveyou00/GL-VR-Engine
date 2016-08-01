#pragma once

#include "GameObject.h"

namespace TileRPG
{
	class PlayerObject : public GlEngine::GameObject
	{
	public:
		PlayerObject();
		~PlayerObject();
		
		void Tick(float delta) override;

		const char *name() override;

		void HandleEvent(GlEngine::Events::Event &evt) override;

		GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;
	
	private:
		float timePassed;
		float direction = 0;
		bool leftPressed, rightPressed, upPressed, downPressed, inPressed, outPressed;
	};
}