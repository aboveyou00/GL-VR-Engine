#pragma once

#include "IService.h"
#include "IComponent.h"

namespace TileRPG
{
    class ITile;

    class TileManager : public GlEngine::IComponent, public GlEngine::IService
    {
    public:
        TileManager();
        ~TileManager();

        bool Initialize();
        void Shutdown();

        bool RegisterTile(ITile *tile);
        ITile *GetTile(int tileId);
        inline ITile *operator[](int tileId)
        {
            return GetTile(tileId);
        }

    private:
        static const int MAX_TILE_ID = 0xFF;
        ITile *baseTiles[MAX_TILE_ID] = { nullptr };
    };
};
