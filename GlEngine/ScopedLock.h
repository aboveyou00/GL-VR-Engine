#pragma once

namespace GlEngine
{
    class ScopedLock
    {
    public:
        ScopedLock(std::mutex &mutex);
        ~ScopedLock();

    private:
        std::mutex *_mutex;
    };
}
