#include "stdafx.h"
#include "TileManager.h"
#include "Engine.h"
#include "ITile.h"

namespace TileRPG
{
    TileManager::TileManager()
    {
    }
    TileManager::~TileManager()
    {
    }

    bool TileManager::Initialize()
    {
        auto &engine = GlEngine::Engine::GetInstance();
        auto &services = engine.GetServiceProvider();
        services.RegisterService<TileManager>(this);
        return true;
    }
    void TileManager::Shutdown()
    {
        auto &engine = GlEngine::Engine::GetInstance();
        auto &services = engine.GetServiceProvider();
        services.DeregisterService(this);
    }

    bool TileManager::RegisterTile(ITile *tile)
    {
        auto id = tile->GetTileId();
        if ((*this)[id] != nullptr)
        {
            //TODO: Log warning
            return false;
        }
        if (id >= MAX_TILE_ID || id < 0)
        {
            //TODO: Log warning
            return false;
        }
        baseTiles[id] = tile;
        return true;
    }
    ITile *TileManager::GetTile(int tileId)
    {
        if (tileId < 0 || tileId >= MAX_TILE_ID) return nullptr;
        return baseTiles[tileId];
    }
}
