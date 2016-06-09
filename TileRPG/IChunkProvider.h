#pragma once

#include "ICPSelector.h"

namespace TileRPG
{
    class IChunkProvider
    {
    public:
        virtual Chunk *Get(int x, int z) = 0;
        virtual void Put(Chunk *chunk) = 0;

        virtual bool IsReadOnly() = 0;

        inline ICPSelector operator[](int x)
        {
            return ICPSelector(this, x);
        }
    };
}
