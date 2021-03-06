#pragma once

namespace TileRPG
{
    class Chunk;
    class IChunkProvider;

    struct ICPSelector
    {
        ICPSelector(IChunkProvider *provider, int row);
        ~ICPSelector();

        Chunk *operator[](int z);

    private:
        IChunkProvider *_provider;
        int _row;
    };
}
