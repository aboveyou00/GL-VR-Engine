#pragma once

namespace GlEngine
{
    class ENGINE_SHARED ScopedLock
    {
    public:
        ScopedLock(rt_mutex &mutex);
        ~ScopedLock();

    private:
        rt_mutex *_mutex;
    };
}
