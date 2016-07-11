#pragma once

#include "GameObject.h"
#include "IAudioSource.h"

namespace TileRPG
{
    class TestMusicObject : public GlEngine::GameObject
    {
    public:
        TestMusicObject(const char *loop);
        TestMusicObject(const char *start, const char *loop);
        ~TestMusicObject();

        bool Initialize() override;
        void Tick(float delta) override;
        void Shutdown() override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

    private:
        const char *startPath, *loopPath;
        GlEngine::IAudioSource *intro;
        GlEngine::IAudioSource *loop;
    };
}
