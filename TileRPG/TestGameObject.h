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

    private:
        float timePassed;
    };
}
