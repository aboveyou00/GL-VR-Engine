#pragma once

#include "IComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class AlControllerImpl;
    }

    class IAudioSource;

    class ENGINE_SHARED AlController : public IComponent
    {
    private:
        AlController();
        ~AlController();

        static AlController _instance;

    public:
        inline static AlController &GetInstance()
        {
            return _instance;
        }

        bool Initialize();
        void Shutdown();

        IAudioSource *CreateAudioSource();
        void ReleaseAudioSource(IAudioSource *source);

        std::mutex &GetMutex();

        inline Impl::AlControllerImpl *GetImpl()
        {
            return pimpl;
        }

    private:
        Impl::AlControllerImpl *pimpl;
    };
}
