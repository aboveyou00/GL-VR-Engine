#pragma once

namespace GlEngine
{
    class ENGINE_SHARED ScopedLock
    {
    public:
        ScopedLock(std::mutex &mutex);
        ~ScopedLock();

    private:
        std::mutex *_mutex;
    };
}
