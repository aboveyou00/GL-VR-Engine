#include "stdafx.h"
#include "ScopedLock.h"

ScopedLock::ScopedLock(rt_mutex &mutex)
{
    _mutex = &mutex;
    _mutex->lock();
}
ScopedLock::~ScopedLock()
{
    _mutex->unlock();
}
