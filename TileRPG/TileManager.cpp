#include "stdafx.h"
#include "TileManager.h"
#include "Engine.h"
#include "ITile.h"

#include "AirTile.h"
#include "DirtTile.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"

namespace TileRPG
{
    TileManager::TileManager()
        : baseTiles { nullptr }
    {
    }
    TileManager::~TileManager()
    {
    }

    TileManager &TileManager::GetInstance()
    {
        static TileManager __instance;
        return __instance;
    }

    bool TileManager::RegisterTile(ITile *tile)
    {
        auto id = tile->GetTileId();
        if ((*this)[id] != nullptr)
        {
            auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            if (logger != nullptr) logger->Log(GlEngine::LogType::Error, "Tried to register multiple tiles with the ID %d", id);
            return false;
        }
        if (id >= MAX_TILE_ID || id < 0)
        {
            auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            if (logger != nullptr) logger->Log(GlEngine::LogType::Error, "Tried to register a tile with ID out of bounds: %d", id);
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
