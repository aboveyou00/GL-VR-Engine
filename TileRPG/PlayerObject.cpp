#include "stdafx.h"
#include "PlayerObject.h"

#include "LogUtils.h"

#include "Engine.h"
#include "AudioController.h"
#include "IAudioSource.h"

#include "KeyboardEvent.h"

#include "World.h"
#include "WorldLoader.h"
#include "Chunk.h"
#include "BoxBody.h"
#include "Quest.h"

#include "FbxGraphicsObject.h"

#include "Collision.h"
#include "TileCollision.h"
#include "ITile.h"
#include "TileManager.h"

namespace TileRPG
{
    PlayerObject::PlayerObject(World* world, Vector<3> position, Matrix<4, 4> orientation)
        : Entity(new GlEngine::BoxBody(-0.2f, 0.2f, -0.2f, 0.2f, -0.2f, 0.2f), position, orientation),
          upPressed(0), downPressed(0), leftPressed(0), rightPressed(0), inPressed(0), outPressed(0),
          loader(new WorldLoader(world)),
          currentQuest(Quest::FirstQuest(this))
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
        Vector<3> motionVector;
        if (currentQuest->IsPaused()) motionVector = { 0, 0, 0 };
        else
        {
            motionVector = { (leftPressed ? -1 : 0) + (rightPressed ? 1 : 0), 0, (upPressed ? 1 : 0) + (downPressed ? -1 : 0) };
            if (motionVector.LengthSquared() > 0.5) motionVector = motionVector.Normalized(3);
        }
        actor()->body->velocity = {motionVector[0], actor()->body->velocity[1], motionVector[2]};

        auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
        audioCtrl.SetListenerPosition(position);

        auto &tileManager = TileManager::GetInstance();
        GlEngine::TileCollision* col = GetSingleTileCollision(3);
        if (col != nullptr && col->tileId != -1)
        {
            ITile* tile = tileManager.GetTile(col->tileId);
            footsteps->SetSource(tile->footstep_sound());
        }
        else
            footsteps->SetSource(nullptr);

        footsteps->SetPosition(position);
        bool playFootsteps = Vector<3>(motionVector[0], 0, motionVector[2]).LengthSquared() > .5;
        if (playFootsteps && !footsteps->IsPlaying()) footsteps->Play(true);
        else if (!playFootsteps && footsteps->IsPlaying()) footsteps->SetLoop(false);

        loader->Move(Chunk::getChunkCoordsFromTileCoords((int)position[0], (int)position[2]));
        loader->Resize(Chunk::getChunkDimensionsFromTileDimensions(32, 32));

        Entity::Tick(delta);

        currentQuest->Tick(delta);
    }
    void PlayerObject::Shutdown()
    {
        footsteps->Release();
    }

    GlEngine::TileCollision* PlayerObject::GetSingleTileCollision(unsigned side)
    {
        for (GlEngine::Collision* col : actor()->body->currentCollisions)
        {
            if (col->id() == 2)
            {
                auto tcol = (GlEngine::TileCollision*)col;
                if (tcol->side == side)
                    return tcol;
            }
        }
        return nullptr;
    }

    void PlayerObject::Jump()
    {
        if (GetSingleTileCollision(3) != nullptr)
            actor()->body->velocity = { actor()->body->velocity[0], 10.0, actor()->body->velocity[2] };
    }
    
    std::string PlayerObject::name()
    {
        return "PlayerObject";
    }

    void PlayerObject::HandleEvent(GlEngine::Events::Event &evt)
    {
        currentQuest->HandleEvent(evt);
        if (evt.IsHandled()) return;

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

    GlEngine::GraphicsObject *PlayerObject::CreateGraphicsObject(GlEngine::GraphicsContext*)
    {
        return GlEngine::FbxGraphicsObject::Create("Resources/cylinder.fbx");
    }
}
