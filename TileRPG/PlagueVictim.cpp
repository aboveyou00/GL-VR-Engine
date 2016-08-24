#include "stdafx.h"
#include "PlagueVictim.h"
#include "BoxBody.h"
#include "MathUtils.h"
#include "RandomUtils.h"

#include "Engine.h"
#include "AudioController.h"
#include "IAudioSource.h"

#include "FbxGraphicsObject.h"

namespace TileRPG
{
    PlagueVictim::PlagueVictim(Vector<3> position, Matrix<4, 4> orientation)
        : Entity(new GlEngine::BoxBody(-0.2f, 0.2f, -0.2f, 0.2f, -0.2f, 0.2f), position, orientation),
          deltaToNextMove(0),
          isMoving(true)
    {
    }
    PlagueVictim::~PlagueVictim()
    {
    }

    bool PlagueVictim::Initialize()
    {
        auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
        jibberish = audioCtrl.CreateAudioSource();
        jibberish->SetSource(randomJibberish());
        jibberish->SetTerminationCallback([&](GlEngine::IAudioSource *src) {
            src->SetSource(randomJibberish());
        });

        return Entity::Initialize();
    }
    void PlagueVictim::Tick(float delta)
    {
        if ((deltaToNextMove -= delta) <= 0)
        {
            isMoving = !isMoving;
            if (!isMoving)
            {
                deltaToNextMove = GlEngine::Util::random<float>(10);
                actor()->body->velocity = Vector<3> { 0, actor()->body->velocity[1], 0 };
            }
            else
            {
                deltaToNextMove = 2.f;
                auto rotation = Matrix<4, 4>::YawMatrix(GlEngine::Util::random<float>() * (float)360deg);
                actor()->body->velocity = rotation * Vector<3> { 1, actor()->body->velocity[1], 0 };
                std::cout << "Distance: " << actor()->body->velocity.Length() << std::endl;
                jibberish->Play(false);
            }
        }

        Entity::Tick(delta);
        jibberish->SetPosition(position);
    }
    void PlagueVictim::Shutdown()
    {
        jibberish->Release();
    }

    const char *PlagueVictim::name()
    {
        return "PlagueVictim";
    }

    GlEngine::GraphicsObject *PlagueVictim::CreateGraphicsObject(GlEngine::GraphicsContext&)
    {
        return GlEngine::FbxGraphicsObject::Create("Resources/cylinder.fbx");
    }

    const char *const PlagueVictim::randomJibberish()
    {
        static const char *const jibberishSources[] = {
            "Audio/jibberish0.ogg",
            "Audio/jibberish1.ogg"
        };
        auto idx = GlEngine::Util::random<int>(sizeof(jibberishSources) / sizeof(const char *const));
        return jibberishSources[idx];
    }


}
