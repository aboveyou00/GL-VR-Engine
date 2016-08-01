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

template <typename IterT, typename ElemT>
void collection_remove(IterT collection, ElemT item)
{
    auto idx = std::find(collection.begin(), collection.end(), item);
    if (idx != collection.end()) collection.erase(idx);
}
