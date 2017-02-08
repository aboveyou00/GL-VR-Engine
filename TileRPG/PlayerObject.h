#pragma once

#include "Entity.h"

namespace GlEngine
{
    class IAudioSource;
    class TileCollision;
}

namespace TileRPG
{
    class World;
    class WorldLoader;
    class Quest;

    class PlayerObject : public Entity
    {
    public:
        PlayerObject(World *world, Vector<3> position = { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        ~PlayerObject();
        
        bool Initialize() override;
        void Tick(float delta) override;
        void Shutdown() override;

        GlEngine::TileCollision* GetSingleTileCollision(unsigned side);
        void Jump();

        virtual std::string name() override;

        void HandleEvent(GlEngine::Events::Event &evt) override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;

        inline Quest *GetCurrentQuest()
        {
            return currentQuest;
        }

    private:
        GlEngine::IAudioSource *footsteps;
        
        WorldLoader* loader;
        float direction = 0;
        bool leftPressed, rightPressed, upPressed, downPressed, inPressed, outPressed;

        Quest *currentQuest;
    };
}