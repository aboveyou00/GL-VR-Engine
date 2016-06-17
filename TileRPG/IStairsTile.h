#pragma once

#include "ITile.h"

namespace TileRPG
{
    class IStairsTile : public ITile
    {
    public:
        IStairsTile(int tileId);
        ~IStairsTile();
    };
}
