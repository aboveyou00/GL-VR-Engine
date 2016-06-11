#pragma once

namespace TileRPG
{
    class ITile
    {
    public:
        ITile(int tileId, bool solid, bool fullBlock);
        ~ITile();

        inline bool IsSolid()
        {
            return _solid;
        }
        inline bool IsFullBlock()
        {
            return _fullBlock;
        }

    private:
        int _tileId;
        bool _solid, _fullBlock;
    };
}
