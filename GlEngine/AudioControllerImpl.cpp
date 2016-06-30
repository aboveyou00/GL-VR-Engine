#include "stdafx.h"
#include "AudioControllerImpl.h"
#include "Audio.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"

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

        static YSE::sound *sound = nullptr;
        static bool startedPlaying = false;

        bool AudioControllerImpl::Initialize()
        {
            auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
            logger->Log(LogType::Info, "Initializing AudioController...");

            if (!YSE::System().init())
            {
                logger->Log(LogType::FatalErrorC, "Failed to initialize AudioController.");
                return false;
            }

            sound = new YSE::sound();
            sound->create("Audio\\overworld-main.ogg", nullptr, true);
            logger->Log(LogType::Error, "Sound file 'overworld-main.ogg' not found.");
            startedPlaying = false;

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
            if (sound->isReady() && !startedPlaying)
            {
                startedPlaying = true;
                sound->play();
            }
        }

        IAudioSource *AudioControllerImpl::CreateAudioSource()
        {
            return nullptr;
        }
        void AudioControllerImpl::ReleaseAudioSource(IAudioSource *source)
        {
            source;
        }
    }
}
