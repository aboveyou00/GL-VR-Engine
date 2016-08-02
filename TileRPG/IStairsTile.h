#pragma once

#include "ITile.h"

namespace TileRPG
{
    class IStairsTile : public ITile
    {
    protected:
        IStairsTile(int tileId);
        ~IStairsTile();
    };
}
