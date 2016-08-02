#pragma once

namespace TileRPG
{
    class ChunkGraphicsObject;

    class ITile
    {
    public:
        ITile(int tileId, bool solid, bool fullBlock)
            : _tileId(tileId), _solid(solid), _fullBlock(fullBlock)
        {
        }
        ~ITile()
        {
        }

        inline int GetTileId()
        {
            return _tileId;
        }

        inline bool IsSolid()
        {
            return _solid;
        }
        inline bool IsFullBlock()
        {
            return _fullBlock;
        }

        virtual bool IsFlushXm();
        virtual bool IsFlushXp();
        virtual bool IsFlushYm();
        virtual bool IsFlushYp();
        virtual bool IsFlushZm();
        virtual bool IsFlushZp();

        virtual void AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z);

    private:
        int _tileId;
        bool _solid, _fullBlock;
    };
}
