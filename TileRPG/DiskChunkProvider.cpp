#include "stdafx.h"
#include "DiskChunkProvider.h"
#include <assert.h>

namespace TileRPG
{
    DiskChunkProvider::DiskChunkProvider(const char *const path, bool readonly)
        : _readonly(readonly)
    {
        int mode = std::fstream::in;
        if (!readonly) mode |= std::fstream::out;
        _file = new std::fstream(path, mode);
    }
    DiskChunkProvider::~DiskChunkProvider()
    {
        if (_file != nullptr)
        {
            delete _file;
            _file = nullptr;
        }
    }

    Chunk *DiskChunkProvider::Get(int x, int z)
    {
        x; z;
        assert(false);
        return nullptr;
    }
    void DiskChunkProvider::Put(Chunk *chunk)
    {
        chunk;
        assert(false);
    }

    bool DiskChunkProvider::IsReadOnly()
    {
        return _readonly;
    }
}
