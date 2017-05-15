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
bool collection_remove(IterT &collection, ElemT &item)
{
    auto idx = std::find(collection.begin(), collection.end(), item);
    if (idx != collection.end())
    {
        collection.erase(idx);
        return true;
    }
    return false;
}

template <typename TKey, typename TVal>
TVal get_with_default(std::map<TKey, TVal> &map, TKey key, TVal default)
{
    auto it = map.find(key);
    if (it == map.end()) return default;
    else return it->second;
}
