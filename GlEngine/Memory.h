#pragma once

template <typename T>
inline void SafeDelete(T **&ptr)
{
    if (ptr != nullptr)
    {
        delete[] ptr;
        ptr = nullptr;
    }
}
template <typename T>
inline void SafeDeleteVector(std::vector<T*> *&ptr)
{
    if (ptr != nullptr)
    {
        for (size_t q = 0; q < ptr->size(); q++)
            SafeDelete((*ptr)[q]);
        delete ptr;
        ptr = nullptr;
    }
}
template <typename T>
inline void SafeDelete(T *&ptr)
{
    if (ptr != nullptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

template <typename IterT, typename ElemT>
void collection_remove(IterT &collection, ElemT &item)
{
    auto idx = std::find(collection.begin(), collection.end(), item);
    if (idx != collection.end()) collection.erase(idx);
}
