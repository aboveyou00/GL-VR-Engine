#pragma once

namespace TileRPG
{
    enum class ChunkLoadHint : unsigned
    {
        SaveAndRemove = 0,
        Indeterminate = 1,
        LoadAndAdd = 2
    };

    //inline bool operator>(ChunkLoadHint lhs, ChunkLoadHint rhs)
    //{
    //    return static_cast<unsigned>(lhs) > static_cast<unsigned>(rhs);
    //}
    //inline bool operator<(ChunkLoadHint lhs, ChunkLoadHint rhs)
    //{
    //    return static_cast<unsigned>(lhs) < static_cast<unsigned>(rhs);
    //}
    //inline bool operator>=(ChunkLoadHint lhs, ChunkLoadHint rhs)
    //{
    //    return static_cast<unsigned>(lhs) >= static_cast<unsigned>(rhs);
    //}
    //inline bool operator<=(ChunkLoadHint lhs, ChunkLoadHint rhs)
    //{
    //    return static_cast<unsigned>(lhs) <= static_cast<unsigned>(rhs);
    //}
}
