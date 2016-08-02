#pragma once

namespace TileRPG
{
    class ITile;

    class TileManager
    {
    private:
        TileManager();
        ~TileManager();

    public:
        static TileManager &GetInstance();

        bool RegisterTile(ITile *tile);
        ITile *GetTile(int tileId);
        inline ITile *operator[](int tileId)
        {
            return GetTile(tileId);
        }

    private:
        bool initialized = false;
        static const int MAX_TILE_ID = 0xFF;
        ITile *baseTiles[MAX_TILE_ID];
    };
};
