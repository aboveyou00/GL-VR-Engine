#include "stdafx.h"
#include "TestMusicObject.h"

#include "Engine.h"
#include "AudioController.h"

namespace TileRPG
{
    TestMusicObject::TestMusicObject()
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

        intro->SetSource("Audio\\overworld-start.ogg");
        loop->SetSource("Audio\\overworld-main.ogg");

        intro->Play(false);
        intro->SetTerminationCallback([&](GlEngine::IAudioSource*) {
            loop->Play(true);
            //loop->Stop(5000);
        });

        return true;
    }
    void TestMusicObject::Shutdown()
    {
        intro->Release();
        loop->Release();
    }
}
