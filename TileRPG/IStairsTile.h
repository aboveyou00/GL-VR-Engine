#pragma once

#include "ITile.h"

namespace TileRPG
{
    class IStairsTile : public ITile
    {
    protected:
        IStairsTile(int tileId);
        ~IStairsTile();

        bool IsFlushXm() const override;
        bool IsFlushXp() const override;
        bool IsFlushYm() const override;
        bool IsFlushYp() const override;
        bool IsFlushZm() const override;
        bool IsFlushZp() const override;
    };
}
