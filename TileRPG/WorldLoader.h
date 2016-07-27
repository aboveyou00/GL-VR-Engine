#pragma once

#include "Vector.h"
#include "ChunkLoadHint.h"

namespace TileRPG
{
    class World;

    class WorldLoader
    {
    public:
        WorldLoader(World *world);
        ~WorldLoader();

        inline bool IsDirty()
        {
            return dirty;
        }
        inline void ClearDirty()
        {
            dirty = false;
        }

        void Move(int x, int z);
        void Move(Vector<2, int> pos);
        void Resize(int width, int depth);
        void Resize(Vector<2, int> size);

        inline Vector<2, int> GetSize()
        {
            return size;
        }
        inline int GetWidth()
        {
            return size[0];
        }
        inline int GetDepth()
        {
            return size[1];
        }
        inline Vector<2, int> GetPosition()
        {
            return position;
        }
        inline int GetX()
        {
            return position[0];
        }
        inline int GetZ()
        {
            return position[1];
        }

        inline ChunkLoadHint GetChunkLoadHint(Vector<2, int> xz)
        {
            return GetChunkLoadHint(xz[0], xz[1]);
        }
        ChunkLoadHint GetChunkLoadHint(int x, int z);

    private:
        World *world;
        Vector<2, int> position, size;
        bool dirty;
    };
}
