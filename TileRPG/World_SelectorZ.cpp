#include "stdafx.h"
#include "World.h"

namespace TileRPG
{
    __SelectorZ::__SelectorZ(int x, int y, World *world)
        : x(x), y(y), world(world)
    {
    }
    __SelectorZ::~__SelectorZ()
    {
    }

    int __SelectorZ::operator[](int z)
    {
        return world->GetTileInfo(x, y, z);
    }
}
