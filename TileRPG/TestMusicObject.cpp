#include "stdafx.h"
#include "TestMusicObject.h"

#include "Engine.h"
#include "AudioController.h"
#include "GraphicsObject.h"
#include "GraphicsContext.h"

#include "ObjGraphicsObject.h"

namespace TileRPG
{
    TestMusicObject::TestMusicObject(const char *loop)
        : TestMusicObject(nullptr, loop)
    {
    }
    TestMusicObject::TestMusicObject(const char *start, const char *loop)
        : startPath(start), loopPath(loop)
    {
    }
    TestMusicObject::~TestMusicObject()
    {
    }

    bool TestMusicObject::Initialize()
    {
        if (!GameObject::Initialize()) return false;

        auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
        intro = audioCtrl.CreateAudioSource();
        loop = audioCtrl.CreateAudioSource();

        //if (startPath != nullptr)
        //{
        //    intro->SetSource(startPath);
        //    loop->SetSource(loopPath);

        //    intro->Play(false);
        //    intro->SetTerminationCallback([&](GlEngine::IAudioSource*) {
        //        loop->Play(true);
        //    });
        //}
        //else
        //{
        //    loop->SetSource(loopPath);

        //    loop->Play(true);
        //}

        return true;
    }
    void TestMusicObject::Shutdown()
    {
        intro->Release();
        loop->Release();
    }

    GlEngine::GraphicsObject *TestMusicObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
    {
        return GlEngine::ObjGraphicsObject::Create("suzanne.obj");
    }
}
