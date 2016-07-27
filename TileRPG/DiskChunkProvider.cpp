#include "stdafx.h"
#include "DiskChunkProvider.h"
#include <assert.h>

namespace TileRPG
{
    DiskChunkProvider::DiskChunkProvider(const char *const path, bool readonly)
        : path(path), _readonly(readonly)
    {
    }
    DiskChunkProvider::~DiskChunkProvider()
    {
        Shutdown();
    }

    bool DiskChunkProvider::Initialize()
    {
        int mode = std::fstream::in;
        if (!_readonly) mode |= std::fstream::out;
        _file = new std::fstream(path, mode);
        return !!*_file;
    }
    void DiskChunkProvider::Shutdown()
    {
        if (_file != nullptr)
        {
            _file->close();
            delete _file;
            _file = nullptr;
        }
    }

    const char *DiskChunkProvider::name()
    {
        return "DiskChunkProvider";
    }

    Chunk *DiskChunkProvider::Get(int x, int z)
    {
        assert(_file && !!*_file);

        x; z;
        assert(false);
        return nullptr;
    }
    void DiskChunkProvider::Put(Chunk *chunk)
    {
        assert(_file && !!*_file);

        chunk;
        assert(false);
    }

    bool DiskChunkProvider::IsReadOnly()
    {
        return _readonly;
    }
}
