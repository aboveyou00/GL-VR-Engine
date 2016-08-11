#pragma once

#include "ITileMacros.h"

namespace TileRPG
{
    class ChunkGraphicsObject;

    class ITile
    {
    protected:
        ITile(int tileId, bool solid, bool fullBlock)
            : _tileId(tileId), _solid(solid), _fullBlock(fullBlock)
        {
        }
        ~ITile()
        {
        }

    public:
        inline int GetTileId()
        {
            return _tileId;
        }

        inline bool IsSolid() const
        {
            return _solid;
        }
        inline bool IsFullBlock() const
        {
            return _fullBlock;
        }

        virtual bool IsFlushXm() const;
        virtual bool IsFlushXp() const;
        virtual bool IsFlushYm() const;
        virtual bool IsFlushYp() const;
        virtual bool IsFlushZm() const;
        virtual bool IsFlushZp() const;

        virtual void AddToChunkGraphicsObject(ChunkGraphicsObject &chunkGobj, int x, int y, int z);

        virtual const char *footstep_sound();

    protected:
        ITile *getTile(int tileId);

    private:
        int _tileId;
        bool _solid, _fullBlock;
    };
}
