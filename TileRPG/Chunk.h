#pragma once

namespace TileRPG
{
    class ITile;

    class Chunk
    {
    public:
        Chunk(int offx, int offz);
        ~Chunk();

        static const int TILES_PER_CHUNK_X = 16;
        static const int TILES_PER_CHUNK_Z = 16;

        inline bool IsDirty()
        {
            return _dirty;
        }

        inline ITile *GetTileInfoGlobal(int tileX, int tileY, int tileZ)
        {
            assert(tileX >= TILES_PER_CHUNK_X * GetX());
            assert(tileX < TILES_PER_CHUNK_X * (GetX() + 1));
            assert(tileZ >= TILES_PER_CHUNK_Z * GetZ());
            assert(tileZ < TILES_PER_CHUNK_Z * (GetZ() + 1));
            return GetTileInfo(tileX % TILES_PER_CHUNK_X, tileY, tileZ % TILES_PER_CHUNK_Z);
        }
        virtual ITile *GetTileInfo(int tileX, int tileY, int tileZ) = 0;

        inline int GetX()
        {
            return x;
        }
        inline int GetZ()
        {
            return z;
        }

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
