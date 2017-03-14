#pragma once

#include "IAudioSource.h"
#include "Audio.h"

namespace GlEngine
{
    class YseAudioSource : public IAudioSource
    {
    public:
        YseAudioSource();
        ~YseAudioSource();

        virtual void SetSource(std::string filename) override;
        virtual void SetPosition(Vector<3> &&position) override;
        virtual void SetSpeed(Vector<3> &speed) override;

        virtual bool Play(bool loop = false) override;
        virtual void Stop(unsigned millis = 0) override;
        virtual void SetLoop(bool loop) override;

        virtual bool IsPlaying() override;

        virtual float volume() override;
        virtual void SetVolume(float volume) override;

        virtual void Update() override;

    private:
        YSE::sound *sound;
        Vector<3> pos, vel;
        std::string source;
        bool isPlaying, soundStarted;
        float _volume;
    };
}
