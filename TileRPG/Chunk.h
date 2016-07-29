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
        ITile *GetTileInfo(int tileX, int tileY, int tileZ);
        inline void SetTileInfoGlobal(int tileX, int tileY, int tileZ, ITile *tile)
        {
            assert(tileX >= TILES_PER_CHUNK_X * GetX());
            assert(tileX < TILES_PER_CHUNK_X * (GetX() + 1));
            assert(tileZ >= TILES_PER_CHUNK_Z * GetZ());
            assert(tileZ < TILES_PER_CHUNK_Z * (GetZ() + 1));
            SetTileInfo(tileX % TILES_PER_CHUNK_X, tileY, tileZ % TILES_PER_CHUNK_Z, tile);
        }
        void SetTileInfo(int tileX, int tileY, int tileZ, ITile *tile);

        inline int GetX()
        {
            return x;
        }
        inline int GetZ()
        {
            return z;
        }

        inline Vector<2, int> getChunkCoordsFromTileCoords(Vector<2, int> xz)
        {
            return getChunkCoordsFromTileCoords(xz[0], xz[1]);
        }
        static Vector<2, int> getChunkCoordsFromTileCoords(int x, int z);
        inline Vector<2, int> getChunkDimensionsFromTileDimensions(Vector<2, int> xz)
        {
            return getChunkDimensionsFromTileDimensions(xz[0], xz[1]);
        }
        static Vector<2, int> getChunkDimensionsFromTileDimensions(int x, int z);

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
