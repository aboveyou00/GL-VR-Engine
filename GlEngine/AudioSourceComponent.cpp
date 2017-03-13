#include "stdafx.h"
#include "AudioSourceComponent.h"
#include "GameObject.h"
#include "AudioController.h"
#include "IAudioSource.h"
#include "StringUtils.h"

namespace GlEngine
{
    AudioSourceComponent::AudioSourceComponent(std::string name, std::string source)
        : GameComponent(name)
    {
        auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
        _source = audioCtrl.CreateAudioSource();
        if (!Util::is_empty_or_ws(source)) _source->SetSource(source);
    }
    AudioSourceComponent::~AudioSourceComponent()
    {
    }

    void AudioSourceComponent::Tick(float)
    {
        auto transform = gameObject()->globalTransform();
        source()->SetPosition(transform->position());
    }

    IAudioSource *AudioSourceComponent::source()
    {
        return _source;
    }
}
