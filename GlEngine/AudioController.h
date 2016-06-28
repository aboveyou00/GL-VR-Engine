#pragma once

#include "IGameComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class AudioControllerImpl;
    }

    class IAudioSource;

    class ENGINE_SHARED AudioController : public IGameComponent
    {
    private:
        AudioController();
        ~AudioController();

        static AudioController _instance;

    public:
        inline static AudioController &GetInstance()
        {
            return _instance;
        }

        bool Initialize();
        void Shutdown();

        void Tick(float delta);

        IAudioSource *CreateAudioSource();
        void ReleaseAudioSource(IAudioSource *source);

        rt_mutex &GetMutex();

        inline Impl::AudioControllerImpl *GetImpl()
        {
            return pimpl;
        }

    private:
        Impl::AudioControllerImpl *pimpl;
    };
}
