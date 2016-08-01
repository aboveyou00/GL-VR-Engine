#include "stdafx.h"
#include "DummyChunkProvider.h"

namespace TileRPG
{
    DummyChunkProvider::DummyChunkProvider()
    {
    }
    DummyChunkProvider::~DummyChunkProvider()
    {
        Shutdown();
    }

    bool DummyChunkProvider::Initialize()
    {
        return true;
    }
    void DummyChunkProvider::Shutdown()
    {
    }

    const char *DummyChunkProvider::name()
    {
        return "DummyChunkProvider";
    }

    Chunk *DummyChunkProvider::Get(int x, int z)
    {
        auto &cachedChunk = getCache(x, z);
        if (cachedChunk != nullptr) return cachedChunk;

        return putCache(createDefaultChunk(x, z));
    }
    bool DummyChunkProvider::Put(Chunk*)
    {
        return false;
    }

    bool DummyChunkProvider::IsReadOnly()
    {
        return true;
    }
}
