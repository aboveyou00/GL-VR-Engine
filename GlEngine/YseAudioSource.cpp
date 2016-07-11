#include "stdafx.h"
#include "YseAudioSource.h"

namespace GlEngine
{
    YseAudioSource::YseAudioSource()
        : sound(nullptr), isPlaying(false), soundStarted(false)
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

    void YseAudioSource::SetSource(const char *const filename)
    {
        if (sound != nullptr)
        {
            Stop();
            delete sound;
            sound = nullptr;
        }
        sound = new YSE::sound();
        sound->create(filename);
    }
    void YseAudioSource::SetPosition(Vector<3> &position)
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

    void YseAudioSource::Update()
    {
        if (sound != nullptr)
        {
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
