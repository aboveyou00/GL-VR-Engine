#pragma once

#include "ICPSelector.h"
#include "IComponent.h"

namespace TileRPG
{
    class IChunkProvider : public GlEngine::IComponent
    {
    public:
        IChunkProvider();
        ~IChunkProvider();

        bool Initialize() override = 0;
        void Shutdown() override = 0;

        inline Chunk *Get(Vector<2, int> xz)
        {
            return Get(xz[0], xz[1]);
        }
        virtual Chunk *Get(int x, int z) = 0;
        virtual void Put(Chunk *chunk) = 0;

        virtual bool IsReadOnly() = 0;

        inline ICPSelector operator[](int x)
        {
            return ICPSelector(this, x);
        }
    };
}
