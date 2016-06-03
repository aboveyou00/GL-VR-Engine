#pragma once

namespace TileRPG
{
    class Tile;

    class Chunk
    {
    public:
        Chunk(int offX, int offY);
        ~Chunk();

        inline bool IsDirty()
        {
            return _dirty;
        }

        Tile *GetTileInfo(int tileX, int tileY, int tileZ);

    private:
        bool _dirty;
    };
}
