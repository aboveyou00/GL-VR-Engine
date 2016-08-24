#include "stdafx.h"
#include "PlayerObject.h"

#include "Engine.h"
#include "AudioController.h"
#include "IAudioSource.h"

#include "KeyboardEvent.h"

#include "World.h"
#include "WorldLoader.h"
#include "Chunk.h"
#include "BoxBody.h"

#include "FbxGraphicsObject.h"

namespace TileRPG
{
    PlayerObject::PlayerObject(World* world, Vector<3> position, Matrix<4, 4> orientation)
		: Entity(new GlEngine::BoxBody(-0.2f, 0.2f, -0.2f, 0.2f, -0.2f, 0.2f), position, orientation),
          upPressed(0), downPressed(0), leftPressed(0), rightPressed(0), inPressed(0), outPressed(0),
		  loader(new WorldLoader(world))
	{
	}
	PlayerObject::~PlayerObject()
	{
        SafeDelete(loader);
	}

    bool PlayerObject::Initialize()
    {
        auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
        footsteps = audioCtrl.CreateAudioSource();

        footsteps->SetSource("Audio/footstep-grass.wav");

        return true;
    }
    void PlayerObject::Tick(float delta)
	{
		auto motionVector = Vector<3>{ (leftPressed ? -1 : 0) + (rightPressed ? 1 : 0), 0, (upPressed ? 1 : 0) + (downPressed ? -1 : 0) };
		if (motionVector.LengthSquared() > 0.5) motionVector = motionVector.Normalized(3);
		actor()->body->velocity = {motionVector[0], actor()->body->velocity[1], motionVector[2]};

		auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
		audioCtrl.SetListenerPosition(position);

        footsteps->SetPosition(position);
        bool playFootsteps = Vector<3>(motionVector[0], 0, motionVector[2]).LengthSquared() > .5;
        if (playFootsteps && !footsteps->IsPlaying()) footsteps->Play(true);
        else if (!playFootsteps && footsteps->IsPlaying()) footsteps->SetLoop(false);

		loader->Move(Chunk::getChunkCoordsFromTileCoords((int)position[0], (int)position[2]));
		loader->Resize(Chunk::getChunkDimensionsFromTileDimensions(32, 32));

        Entity::Tick(delta);
	}
    void PlayerObject::Shutdown()
    {
        footsteps->Release();
    }

	void PlayerObject::Jump()
	{
		actor()->body->velocity = { actor()->body->velocity[0], 4.0, actor()->body->velocity[2] };
	}
	
	const char *PlayerObject::name()
	{
		return "PlayerObject";
	}

	void PlayerObject::HandleEvent(GlEngine::Events::Event &evt)
	{
		auto kbevt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
		if (kbevt == nullptr) return;
		if (kbevt->GetEventType() != GlEngine::Events::KeyboardEventType::KeyPressed &&
            kbevt->GetEventType() != GlEngine::Events::KeyboardEventType::KeyReleased) return;

		auto pressed = kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyPressed;
		switch (kbevt->GetVirtualKeyCode())
		{
		case VK_UP:
			upPressed = pressed;
			break;
		case VK_DOWN:
			downPressed = pressed;
			break;
		case VK_LEFT:
			leftPressed = pressed;
			break;
		case VK_RIGHT:
			rightPressed = pressed;
			break;
		case VK_LETTER<'q'>():
			inPressed = pressed;
			break;
		case VK_LETTER<'a'>():
			outPressed = pressed;
			break;
		case VK_SPACE:
			if (pressed)
				Jump();
            break;
		}
	}

	GlEngine::GraphicsObject *PlayerObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
	{
		return GlEngine::FbxGraphicsObject::Create("Resources/cylinder.fbx");
		//return GlEngine::ObjGraphicsObject::Create("Resources/suzanne.obj", "Shaders", "direct_light_tex", "Textures/checkers.png");
	}
}
