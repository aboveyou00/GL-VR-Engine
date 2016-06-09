#pragma once

namespace TileRPG
{
    class ITile;

    class Chunk
    {
    public:
        Chunk(int offx, int offz)
            : x(offx), z(offz), _dirty(false)
        {
        }
        ~Chunk()
        {
        }

        inline bool IsDirty()
        {
            return _dirty;
        }

        virtual ITile *GetTileInfo(int tileX, int tileY, int tileZ) = 0;

    protected:
        void SetDirty()
        {
            _dirty = true;
        }

    private:
        int x, z;
        bool _dirty;
    };
}
