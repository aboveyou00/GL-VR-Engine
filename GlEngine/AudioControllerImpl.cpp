#include "stdafx.h"
#include "AudioControllerImpl.h"
#include "Audio.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"

#include "YseAudioSource.h"

namespace GlEngine
{
    namespace Impl
    {
        AudioControllerImpl::AudioControllerImpl()
        {
        }
        AudioControllerImpl::~AudioControllerImpl()
        {
        }

        bool AudioControllerImpl::Initialize()
        {
            auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
            logger->Log(LogType::Info, "Initializing AudioController...");

            if (!YSE::System().init())
            {
                logger->Log(LogType::FatalErrorC, "Failed to initialize AudioController.");
                return false;
            }

            logger->Log(LogType::Info, "AudioController initialization successful.");
            return true;
        }
        void AudioControllerImpl::Shutdown()
        {
            auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
            logger->Log(LogType::Info, "~Shutting down AudioController");

            YSE::System().close();
        }

        void AudioControllerImpl::Tick(float)
        {
            YSE::System().update();
        }

        IAudioSource *AudioControllerImpl::CreateAudioSource()
        {
            //TODO: keep a list of audio sources so that we can be sure to release them all...
            return new YseAudioSource();
        }
        void AudioControllerImpl::ReleaseAudioSource(IAudioSource *source)
        {
            //TODO: release this audio source
            source->Stop();
            source;
        }

        void AudioControllerImpl::SetListenerPosition(Vector<3> position)
        {
            YSE::Listener().setPosition(YSE::Vec(position[0], position[1], position[2]));
        }
    }
}
