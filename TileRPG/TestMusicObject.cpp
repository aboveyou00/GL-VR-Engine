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
        audio = audioCtrl.CreateAudioSource();

        audio->SetSource("Audio\\overworld-main.ogg", true);
        audio->Play();

        return true;
    }
    void TestMusicObject::Shutdown()
    {
        audio->Release();
    }
}
