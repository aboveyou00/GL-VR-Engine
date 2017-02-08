#pragma once

#include "Entity.h"

namespace GlEngine
{
    class IAudioSource;
}

namespace TileRPG
{
    class PlagueVictim : public Entity
    {
    public:
        PlagueVictim(Vector<3> position = { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        ~PlagueVictim();

        virtual bool Initialize() override;
        virtual void Tick(float delta) override;
        virtual void Shutdown() override;

        virtual std::string name() override;
        
        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;

    private:
        float deltaToNextMove;
        bool isMoving;

        GlEngine::IAudioSource *jibberish;
        const char *const randomJibberish();
    };
}
