#pragma once

#include "IChunkProvider.h"

namespace TileRPG
{
    namespace Impl
    {
        class DCPChunkImpl;
    }

    class DummyChunkProvider : public IChunkProvider
    {
    public:
        DummyChunkProvider();
        ~DummyChunkProvider();

        bool Initialize() override;
        void Shutdown() override;

        const char *name() override;

        Chunk *Get(int x, int z) override;
        bool Put(Chunk *chunk) override;

        bool IsReadOnly() override;
    };
}
