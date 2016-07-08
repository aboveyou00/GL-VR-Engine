#pragma once

#include "GameObject.h"

namespace TileRPG
{
    class TestEventObject : public GlEngine::GameObject
    {
    public:
        TestEventObject();
        ~TestEventObject();

        void Tick(float delta) override;

        void HandleEvent(GlEngine::Events::Event &evt) override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

    private:
        float timePassed;
        bool leftPressed, rightPressed, upPressed, downPressed;
    };
}
