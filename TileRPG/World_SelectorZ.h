#pragma once

namespace TileRPG
{
    class World;
    class ITile;

    struct __SelectorZ
    {
    public:
        __SelectorZ(int x, int y, World *world);
        ~__SelectorZ();

        int operator[](int z);

    private:
        int x, y;
        World *world;
    };
}
