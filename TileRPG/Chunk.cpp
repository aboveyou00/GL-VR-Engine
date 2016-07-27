#include "stdafx.h"
#include "Chunk.h"

namespace TileRPG
{
    Chunk::Chunk(int offx, int offz)
        : x(offx), z(offz), _dirty(false)
    {
    }
    Chunk::~Chunk()
    {
    }
}
