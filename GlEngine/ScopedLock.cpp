#include "stdafx.h"
#include "ScopedLock.h"

namespace GlEngine
{
    ScopedLock::ScopedLock(std::mutex &mutex)
    {
        _mutex = &mutex;
        _mutex->lock();
    }
    ScopedLock::~ScopedLock()
    {
        _mutex->unlock();
    }
}
