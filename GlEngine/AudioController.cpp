#include "stdafx.h"
#include "AudioController.h"
#include "AudioControllerImpl.h"

namespace GlEngine
{
    AudioController::AudioController()
        : pimpl(new Impl::AudioControllerImpl())
    {
    }
    AudioController::~AudioController()
    {
        if (pimpl != nullptr)
        {
            delete pimpl;
            pimpl = nullptr;
        }
    }

    AudioController AudioController::_instance;

    bool AudioController::Initialize()
    {
        return pimpl->Initialize();
    }
    void AudioController::Shutdown()
    {
        pimpl->Shutdown();
    }

    void AudioController::Tick(float delta)
    {
        pimpl->Tick(delta);
    }

    IAudioSource *AudioController::CreateAudioSource()
    {
        return pimpl->CreateAudioSource();
    }
    void AudioController::ReleaseAudioSource(IAudioSource *source)
    {
        pimpl->ReleaseAudioSource(source);
    }

    rt_mutex &AudioController::GetMutex()
    {
        return pimpl->GetMutex();
    }
}
