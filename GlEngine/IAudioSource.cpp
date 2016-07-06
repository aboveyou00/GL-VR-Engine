#include "stdafx.h"
#include "IAudioSource.h"

#include "Engine.h"
#include "AudioController.h"

namespace GlEngine
{
    IAudioSource::IAudioSource()
    {
        _cb = nullptr;
    }
    IAudioSource::~IAudioSource()
    {
    }

    void IAudioSource::Release()
    {
        auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
        audioCtrl.ReleaseAudioSource(this);
    }
}
