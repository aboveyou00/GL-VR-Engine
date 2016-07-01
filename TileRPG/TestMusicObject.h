#pragma once

#include "GameObject.h"
#include "IAudioSource.h"

namespace TileRPG
{
    class TestMusicObject : public GlEngine::GameObject
    {
    public:
        TestMusicObject();
        ~TestMusicObject();

        bool Initialize() override;
        void Shutdown() override;

    private:
        GlEngine::IAudioSource *intro;
        GlEngine::IAudioSource *loop;
    };
}
