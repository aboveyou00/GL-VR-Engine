#include "stdafx.h"
#include "YseAudioSource.h"

namespace GlEngine
{
    YseAudioSource::YseAudioSource()
    {
        isPlaying = false;
        soundStarted = false;
    }
    YseAudioSource::~YseAudioSource()
    {
    }

    void YseAudioSource::SetSource(const char *const filename)
    {
        sound.create(filename);
    }
    void YseAudioSource::SetPosition(Vector<3> &position)
    {
        sound.setPosition(YSE::Vec(position[0], position[1], position[2]));
    }
    void YseAudioSource::SetSpeed(Vector<3> &)
    {
        //TODO: set the sound velocity
        //sound.setSpeed(YSE::Vec(speed[0], speed[1], speed[2]));
    }
    bool YseAudioSource::Play(bool loop)
    {
        if (!sound.isValid()) return false;
        sound.play();
        sound.setLooping(loop);
        isPlaying = true;
        soundStarted = false;
        return true;
    }
    void YseAudioSource::Stop(unsigned millis)
    {
        if (sound.isPlaying())
        {
            if (millis > 0) sound.fadeAndStop(millis);
            else sound.stop();
            isPlaying = false;
        }
    }

    void YseAudioSource::Update()
    {
        if (isPlaying)
        {
            if (!soundStarted)
            {
                if (sound.isPlaying()) soundStarted = true;
            }
            else
            {
                if (!sound.isPlaying())
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
            if (sound.isPlaying())
            {
                isPlaying = true;
                soundStarted = true;
            }
        }
    }
}
