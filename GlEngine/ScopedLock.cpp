#include "stdafx.h"
#include "ScopedLock.h"

namespace GlEngine
{
    ScopedLock::ScopedLock(rt_mutex &mutex)
    {
        _mutex = &mutex;
        _mutex->lock();
    }
    ScopedLock::~ScopedLock()
    {
        _mutex->unlock();
    }
}
