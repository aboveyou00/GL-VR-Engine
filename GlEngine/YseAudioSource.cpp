#include "stdafx.h"
#include "YseAudioSource.h"
#include "StringUtils.h"

void func()
{
    YSE::ChannelFX();
}

namespace GlEngine
{
    YseAudioSource::YseAudioSource()
        : sound(nullptr), isPlaying(false), soundStarted(false), source(""s)
    {
    }
    YseAudioSource::~YseAudioSource()
    {
        if (sound != nullptr)
        {
            Stop();
            delete sound;
            sound = nullptr;
        }
    }

    void YseAudioSource::SetSource(std::string filename)
    {
        if (filename == source || filename == source) return;
        if (sound != nullptr)
        {
            Stop();
            delete sound;
            sound = nullptr;
        }
        source = filename;
        if (!Util::is_empty_or_ws(filename))
        {
            sound = new YSE::sound();
            sound->create(filename.c_str());
        }
    }
    void YseAudioSource::SetPosition(Vector<3> &&position)
    {
        pos = position;
    }
    void YseAudioSource::SetSpeed(Vector<3> &velocity)
    {
        vel = velocity;
    }

    bool YseAudioSource::Play(bool loop)
    {
        if (sound != nullptr && sound->isValid())
        {
            sound->play();
            sound->setLooping(loop);
            isPlaying = true;
            soundStarted = false;
            return true;
        }
        return false;
    }
    void YseAudioSource::Stop(unsigned millis)
    {
        if (sound != nullptr && sound->isPlaying())
        {
            if (millis > 0) sound->fadeAndStop(millis);
            else sound->stop();
            isPlaying = false;
        }
    }
    void YseAudioSource::SetLoop(bool loop)
    {
        if (sound != nullptr) sound->setLooping(loop);
    }

    bool YseAudioSource::IsPlaying()
    {
        return isPlaying;
    }

    void YseAudioSource::Update()
    {
        if (sound != nullptr)
        {
            if (!sound->isValid() || !sound->isReady())
                return;
            sound->setPosition(YSE::Vec(pos[0], pos[1], pos[2]));
            //TODO: set the sound velocity
            if (isPlaying)
            {
                if (!soundStarted)
                {
                    if (sound->isPlaying()) soundStarted = true;
                }
                else
                {
                    if (!sound->isPlaying())
                    {
                        isPlaying = false;
                        soundStarted = false;
                        auto cb = GetTerminationCallback();
                        if (cb) cb(this);
                    }
                }
            }
            else
            {
                if (sound->isPlaying())
                {
                    isPlaying = true;
                    soundStarted = true;
                }
            }
        }
    }
}
