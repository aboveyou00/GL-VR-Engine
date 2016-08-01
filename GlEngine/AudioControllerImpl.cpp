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
            for (size_t q = 0; q < sources.size(); q++)
            {
                auto &src = *sources.at(q);
                src.Update();
            }

            YSE::System().update();
        }

        IAudioSource *AudioControllerImpl::CreateAudioSource()
        {
            auto new_source = new YseAudioSource();
            sources.push_back(new_source);
            return new_source;
        }
        void AudioControllerImpl::ReleaseAudioSource(IAudioSource *source)
        {
            source->Stop();
            auto idx = std::find(sources.begin(), sources.end(), source);
            if (idx != sources.end()) sources.erase(idx);
        }

        void AudioControllerImpl::SetListenerPosition(Vector<3> position)
        {
            YSE::Listener().setPosition(YSE::Vec(position[0], position[1], position[2]));
        }
        const char *AudioControllerImpl::name()
        {
            return "AudioControllerImpl";
        }
    }
}
