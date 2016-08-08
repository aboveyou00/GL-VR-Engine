#pragma once

#include "IChunkProvider.h"

namespace TileRPG
{
    namespace Impl
    {
        class DCPChunkImpl;
    }

    class DiskChunkProvider : public IChunkProvider
    {
    public:
        DiskChunkProvider(const char *const path, bool readonly = false);
        ~DiskChunkProvider();

        bool Initialize() override;
        void Shutdown() override;

        const char *name() override;

        Chunk *Get(int x, int z) override;
        bool Put(Chunk *chunk) override;

        bool IsReadOnly() override;

    private:
        bool _readonly;
        const char *const path;

        const char *const getChunkPath(int x, int z);
        Chunk *readChunk(int x, int z, std::istream &stream);
        bool writeChunk(Chunk *chunk, std::ostream &stream);
    };
}
