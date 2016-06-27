#pragma once

#include "GameObject.h"

namespace TileRPG
{
    class TestGameObject : public GlEngine::GameObject
    {
    public:
        TestGameObject();
        ~TestGameObject();

        bool Initialize() override;
        void Tick(float delta) override;

        void HandleEvent(GlEngine::Events::Event &evt) override;

    private:
        float timePassed;
        bool leftPressed, rightPressed, upPressed, downPressed;
    };
}
