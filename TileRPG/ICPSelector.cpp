#include "stdafx.h"
#include "IChunkProvider.h"

namespace TileRPG
{
    ICPSelector::ICPSelector(IChunkProvider * provider, int row)
    {
        _provider = provider;
        _row = row;
    }

    Chunk *ICPSelector::operator[](int z)
    {
        return _provider->Get(_row, z);
    }
}
