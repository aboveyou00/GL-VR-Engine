#pragma once

#include "IChunkProvider.h"

namespace TileRPG
{
    class DiskChunkProvider : public IChunkProvider
    {
    public:
        DiskChunkProvider(const char *const path, bool readonly = false);
        ~DiskChunkProvider();

        bool Initialize() override;
        void Shutdown() override;

        virtual const char * name() override;

        Chunk *Get(int x, int z) override;
        void Put(Chunk *chunk) override;

        bool IsReadOnly() override;

    private:
        bool _readonly;
        const char *const path;
        std::fstream *_file;
    };
}
