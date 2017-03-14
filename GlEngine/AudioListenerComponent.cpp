#include "stdafx.h"
#include "AudioListenerComponent.h"
#include "GameObject.h"
#include "AudioController.h"
#include "StringUtils.h"

namespace GlEngine
{
    AudioListenerComponent::AudioListenerComponent(std::string name)
        : GameComponent(Util::is_empty_or_ws(name) ? "AudioListenerComponent" : name)
    {
    }
    AudioListenerComponent::~AudioListenerComponent()
    {
    }

    void AudioListenerComponent::Tick(float delta)
    {
        GameComponent::Tick(delta);

        auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
        audioCtrl.SetListenerPosition(gameObject()->globalTransform()->position());
    }
}
