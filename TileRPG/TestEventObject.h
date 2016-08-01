#pragma once

#include "GameObject.h"

namespace TileRPG
{
    class World;
    class WorldLoader;

    class TestEventObject : public GlEngine::GameObject
    {
    public:
        TestEventObject(World *world);
        ~TestEventObject();

        void Tick(float delta) override;

        const char *name() override;

        void HandleEvent(GlEngine::Events::Event &evt) override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

    private:
        float timePassed;
        bool leftPressed, rightPressed, upPressed, downPressed, inPressed, outPressed;
        WorldLoader *loader;
    };
}
