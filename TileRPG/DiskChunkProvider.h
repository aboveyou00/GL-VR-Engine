#pragma once

#include "IChunkProvider.h"

namespace TileRPG
{
    class DiskChunkProvider : public IChunkProvider
    {
    public:
        DiskChunkProvider(const char *const path, bool readonly = false);
        ~DiskChunkProvider();

        Chunk *Get(int x, int z) override;
        void Put(Chunk *chunk) override;

        bool IsReadOnly() override;

    private:
        bool _readonly;
        std::fstream *_file;
    };
}
