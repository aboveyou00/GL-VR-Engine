#pragma once

namespace TileRPG
{
    class ITile
    {
    public:
        ITile(int tileId, bool solid);
        ~ITile();

        inline bool IsSolid()
        {
            return _solid;
        }

    private:
        int _tileId;
        bool _solid;
    };
}