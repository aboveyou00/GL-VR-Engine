#pragma once

#include <mutex>
#include <thread>
#include "ScopedLock.h"

static inline bool TestSetLock(bool &val, std::mutex &mutex, std::function<void()> onSuccess = nullptr)
{
    GlEngine::ScopedLock _lock(mutex);
    if (val) return false;

    val = true;
    if (onSuccess != nullptr) onSuccess();
    return true;
}
static inline void ReleaseLock(bool &val, std::mutex &mutex)
{
    GlEngine::ScopedLock _lock(mutex);
    val = false;
}

template <typename T>
static inline T LockGet(T &val, std::mutex &mutex)
{
    GlEngine::ScopedLock _lock(mutex);
    return val;
}

template <typename T>
static inline void LockSet(T &val, T newVal, std::mutex &mutex)
{
    GlEngine::ScopedLock _lock(mutex);
    val = newVal;
}
