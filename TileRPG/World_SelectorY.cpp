#include "stdafx.h"
#include "World.h"

namespace TileRPG
{
    __SelectorY::__SelectorY(int x, World *world)
        : x(x), world(world)
    {
    }
    __SelectorY::~__SelectorY()
    {
    }

    __SelectorZ __SelectorY::operator[](int y)
    {
        return { x, y, world };
    }
}
