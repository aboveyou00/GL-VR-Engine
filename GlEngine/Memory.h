#pragma once

template <typename T>
inline void SafeDelete(T *&ptr)
{
    delete ptr;
    ptr = nullptr;
}
template <typename T>
inline void SafeDeleteArray(T **&ptr)
{
    delete[] ptr;
    ptr = nullptr;
}
