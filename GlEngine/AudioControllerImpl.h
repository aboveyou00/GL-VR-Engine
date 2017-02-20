#pragma once

#include "IInitializable.h"
#include "YseAudioSource.h"

namespace GlEngine
{
    class IAudioSource;

    namespace Impl
    {
        class AudioControllerImpl : public IInitializable
        {
        public:
            AudioControllerImpl();
            ~AudioControllerImpl();

            virtual bool Initialize() override;
            virtual void Shutdown() override;

            void Tick();

            IAudioSource *CreateAudioSource();
            void ReleaseAudioSource(IAudioSource *source);

            void SetListenerPosition(Vector<3> position);

            rt_mutex &GetMutex();

            virtual std::string name() override;

        private:
            rt_mutex audioMutex;
            std::vector<YseAudioSource*> sources;
        };
    }
}
