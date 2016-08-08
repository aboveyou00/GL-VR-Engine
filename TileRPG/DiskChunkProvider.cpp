#include "stdafx.h"
#include "DiskChunkProvider.h"
#include <assert.h>
#include "PathUtils.h"
#include "Chunk.h"
#include "StringUtils.h"

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

        Chunk *chunk = readChunk(x, z, file);
        if (chunk == nullptr) chunk = createDefaultChunk(x, z);
        return putCache(chunk);
    }
    bool DiskChunkProvider::Put(Chunk *chunk)
    {
        if (_readonly) return false;

        int x = chunk->GetX(),
            z = chunk->GetZ();

        int mode = std::fstream::out | std::fstream::trunc;
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

    Chunk *DiskChunkProvider::readChunk(int chunkx, int chunkz, std::istream &stream)
    {
        Chunk chunk(chunkx, chunkz);
        static const int MAX_BUFF_SIZE = 128;
        static thread_local char word[MAX_BUFF_SIZE];

        int rx, rz;
        unsigned hit;

        stream >> word;
        if (GlEngine::Util::strcmp(word, "x") != 0) return nullptr;
        stream >> rx;
        if (rx != chunkx) return nullptr;

        stream >> word;
        if (GlEngine::Util::strcmp(word, "z") != 0) return nullptr;
        stream >> rz;
        if (rz != chunkz) return nullptr;

        stream >> word;
        if (GlEngine::Util::strcmp(word, "h") != 0) return nullptr;
        stream >> hit;

        for (size_t q = 0; q < hit; q++)
        {
            int sidx;
            stream >> word;
            if (GlEngine::Util::strcmp(word, "s") != 0) return nullptr;
            stream >> sidx;
            for (size_t w = 0; w < Chunk::TILES_PER_CHUNK_X; w++)
                for (size_t e = 0; e < Chunk::TILES_PER_CHUNK_Z; e++)
                {
                    int tile;
                    stream >> tile;
                    chunk.SetTileInfo(w, sidx, e, tile);
                }
        }

        return new Chunk(chunk);
    }
    bool DiskChunkProvider::writeChunk(Chunk *chunk, std::ostream &stream)
    {
        unsigned maxy = (unsigned)chunk->GetMaxY();
        stream << "x " << chunk->GetX() << " z " << chunk->GetZ() << " h " << maxy << std::endl;
        for (size_t y = 0; y < maxy; y++)
        {
            stream << "s " << y << " ";
            for (size_t x = 0; x < Chunk::TILES_PER_CHUNK_X; x++)
                for (size_t z = 0; z < Chunk::TILES_PER_CHUNK_Z; z++)
                    stream << chunk->GetTileInfo(x, y, z) << " ";
            stream << std::endl;
        }
        return true;
    }
}
