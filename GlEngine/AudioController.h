#pragma once

#include "IInitializable.h"
#include "IAudioSource.h"

namespace GlEngine
{
    namespace Impl
    {
        class AudioControllerImpl;
    }

    class ENGINE_SHARED AudioController : public IInitializable
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

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        void Tick(float delta);

        IAudioSource *CreateAudioSource();
        void ReleaseAudioSource(IAudioSource *source);

        void SetListenerPosition(Vector<3> position);

        rt_mutex &GetMutex();

        virtual std::string name() override;

        inline Impl::AudioControllerImpl *GetImpl()
        {
            return pimpl;
        }

    private:
        Impl::AudioControllerImpl *pimpl;
    };
}
