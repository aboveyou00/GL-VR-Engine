#pragma once

#include <mutex>

using rt_mutex = std::recursive_timed_mutex;

#include <thread>
#include "ScopedLock.h"

static inline bool TestSetLock(bool &val, rt_mutex &mutex, std::function<void()> onSuccess = nullptr)
{
    ScopedLock _lock(mutex);
    if (val) return false;

    val = true;
    if (onSuccess != nullptr) onSuccess();
    return true;
}
static inline void ReleaseLock(bool &val, rt_mutex &mutex)
{
    ScopedLock _lock(mutex);
    val = false;
}

template <typename T>
static inline T LockGet(T &val, rt_mutex &mutex)
{
    ScopedLock _lock(mutex);
    return val;
}

template <typename T>
static inline void LockSet(T &val, T newVal, rt_mutex &mutex)
{
    ScopedLock _lock(mutex);
    val = newVal;
}

#include "ThreadType.h"

ENGINE_SHARED std::string &this_thread_name();
ENGINE_SHARED ThreadType &this_thread_type();
