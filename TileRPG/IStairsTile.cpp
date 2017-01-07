#include "stdafx.h"
#include "IStairsTile.h"

namespace TileRPG
{
    IStairsTile::IStairsTile(int tileId)
        : ITile(tileId, true, false)
    {
    }
    IStairsTile::~IStairsTile()
    {
    }

    bool IStairsTile::IsFlushXm() const
    {
        return true;
    }
    bool IStairsTile::IsFlushXp() const
    {
        return false;
    }
    bool IStairsTile::IsFlushYm() const
    {
        return true;
    }
    bool IStairsTile::IsFlushYp() const
    {
        return false;
    }
    bool IStairsTile::IsFlushZm() const
    {
        return false;
    }
    bool IStairsTile::IsFlushZp() const
    {
        return false;
    }
}
