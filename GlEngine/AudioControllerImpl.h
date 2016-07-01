#pragma once

#include "IGameComponent.h"
#include "YseAudioSource.h"

namespace GlEngine
{
    class IAudioSource;

    namespace Impl
    {
        class AudioControllerImpl : public IGameComponent
        {
        public:
            AudioControllerImpl();
            ~AudioControllerImpl();

            bool Initialize();
            void Shutdown();

            void Tick(float delta);

            IAudioSource *CreateAudioSource();
            void ReleaseAudioSource(IAudioSource *source);

            void SetListenerPosition(Vector<3> position);

            inline rt_mutex &GetMutex()
            {
                return audioMutex;
            }

        private:
            rt_mutex audioMutex;
            std::vector<YseAudioSource*> sources;
        };
    }
}
