#pragma once

namespace GlEngine
{
    class ENGINE_SHARED IAudioSource
    {
    public:
        IAudioSource();
        ~IAudioSource();

        virtual void SetSource(const char *const filename, bool loop = false) = 0;
        virtual void SetPosition(Vector<3> &position) = 0;
        virtual void SetSpeed(Vector<3> &speed) = 0;
        virtual bool Play() = 0;
        virtual void Stop() = 0;

        void Release();
    };
}
