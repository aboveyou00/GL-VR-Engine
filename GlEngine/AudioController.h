#pragma once

#include "IGameComponent.h"
#include "IAudioSource.h"

namespace GlEngine
{
    namespace Impl
    {
        class AudioControllerImpl;
    }

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

        void SetListenerPosition(Vector<3> position);

        rt_mutex &GetMutex();

        const char *name() override;

        inline Impl::AudioControllerImpl *GetImpl()
        {
            return pimpl;
        }

    private:
        Impl::AudioControllerImpl *pimpl;
    };
}
