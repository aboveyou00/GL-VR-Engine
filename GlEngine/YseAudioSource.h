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

        void SetSource(const char *const filename, bool loop) override;
        void SetPosition(Vector<3> &position) override;
        void SetSpeed(Vector<3> &speed) override;
        bool Play() override;
        void Stop() override;

    private:
        YSE::sound sound;
    };
}
