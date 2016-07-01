#include "stdafx.h"
#include "YseAudioSource.h"

namespace GlEngine
{
    YseAudioSource::YseAudioSource()
    {
    }
    YseAudioSource::~YseAudioSource()
    {
    }

    void YseAudioSource::SetSource(const char *const filename, bool loop)
    {
        sound.create(filename, nullptr, loop);
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
    bool YseAudioSource::Play()
    {
        sound.play();
        return false;
    }
    void YseAudioSource::Stop()
    {
        sound.stop();
    }
}
