#include "stdafx.h"
#include "DiskChunkProvider.h"
#include <assert.h>
#include "PathUtils.h"
#include "Chunk.h"

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
        return true;
    }
    void DiskChunkProvider::Shutdown()
    {
    }

    const char *DiskChunkProvider::name()
    {
        return "DiskChunkProvider";
    }

    Chunk *DiskChunkProvider::Get(int x, int z)
    {
        Chunk *cachedChunk = getCache(x, z);
        if (cachedChunk != nullptr) return cachedChunk;

        int mode = std::fstream::in;
        std::ifstream file(getChunkPath(x, z), mode);
        if (!file || file.fail()) return putCache(createDefaultChunk(x, z));

        Chunk *chunk = readChunk(file);
        if (chunk == nullptr) chunk = createDefaultChunk(x, z);
        return putCache(chunk);
    }
    bool DiskChunkProvider::Put(Chunk *chunk)
    {
        if (_readonly) return false;

        int x = chunk->GetX(),
            z = chunk->GetZ();

        int mode = std::fstream::out;
        std::ofstream file(getChunkPath(x, z), mode);
        if (!file || file.fail()) return false;

        return writeChunk(putCache(chunk), file);
    }

    bool DiskChunkProvider::IsReadOnly()
    {
        return _readonly;
    }

    const char *const DiskChunkProvider::getChunkPath(int x, int z)
    {
        static const int MAX_FNAME_BUFF = 64;
        static thread_local char fname_buff[MAX_FNAME_BUFF];
        sprintf_s(fname_buff, "chunk_%d_%d.txt", x, z);
        return GlEngine::Util::combinePath(path, fname_buff);
    }

    Chunk *DiskChunkProvider::readChunk(std::istream &stream)
    {
        stream;
        return nullptr;
    }
    bool DiskChunkProvider::writeChunk(Chunk *chunk, std::ostream &stream)
    {
        chunk, stream;
        return false;
    }
}
