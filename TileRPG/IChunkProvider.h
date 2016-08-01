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
        virtual bool Put(Chunk *chunk) = 0;

        virtual bool IsReadOnly() = 0;

        inline ICPSelector operator[](int x)
        {
            return { this, x };
        }

    protected:
        Chunk *createDefaultChunk(int x, int z);

        std::vector<Chunk*> chunkCache;
        Chunk *&getCache(int x, int z);
        Chunk *putCache(Chunk *chunk);
    };
}
