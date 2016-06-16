#pragma once

#include "IGameComponent.h"

namespace GlEngine
{
    class IAudioSource;

    namespace Impl
    {
        class AlControllerImpl : public IComponent
        {
        public:
            AlControllerImpl();
            ~AlControllerImpl();

            bool Initialize();
            void Shutdown();

            IAudioSource *CreateAudioSource();
            void ReleaseAudioSource(IAudioSource *source);

            inline std::mutex &GetMutex()
            {
                return audioMutex;
            }

        private:
            std::mutex audioMutex;
        };
    }
}
