#pragma once
#include "World_SelectorZ.h"

namespace TileRPG
{
    struct __SelectorY
    {
    public:
        __SelectorY(int x, World *world);
        ~__SelectorY();

        __SelectorZ operator[](int y);

    private:
        int x;
        World *world;
    };
}
