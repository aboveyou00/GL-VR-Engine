#pragma once

namespace GlEngine
{
    class ENGINE_SHARED IAudioSource
    {
    public:
        IAudioSource();
        ~IAudioSource();

        virtual void SetSource(std::string filename) = 0;
        virtual void SetPosition(Vector<3> &&position) = 0;
        virtual void SetSpeed(Vector<3> &speed) = 0;

        virtual bool Play(bool loop = false) = 0;
        virtual void Stop(unsigned millis = 0) = 0;
        virtual void SetLoop(bool loop) = 0;

        virtual bool IsPlaying() = 0;

        virtual void Update() = 0;
        
        void Release();

        inline void SetTerminationCallback(std::function<void(IAudioSource*)> cb)
        {
            _cb = cb;
        }
        inline std::function<void(IAudioSource*)> GetTerminationCallback()
        {
            return _cb;
        }

    private:
        std::function<void(IAudioSource*)> _cb;
    };
}
