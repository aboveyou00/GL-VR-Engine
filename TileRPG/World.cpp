#include "stdafx.h"
#include "World.h"
#include "WorldLoader.h"
#include "Chunk.h"

namespace TileRPG
{
    World::World(IChunkProvider *provider)
        : provider(provider),
          chunkProviderLoop(
              [&]() { return initializeLoop(); },
              [&](float delta) { tickLoop(delta); },
              [&]() { shutdownLoop(); }
          ),
          removedWorldLoader(false)
    {
        RequireTick();
    }
    World::~World()
    {
    }

    void World::RegisterWorldLoader(WorldLoader *loader)
    {
        worldLoaders.push_back(loader);
    }
    void World::ReleaseWorldLoader(WorldLoader *loader)
    {
        auto idx = std::find(worldLoaders.begin(), worldLoaders.end(), loader);
        if (idx != worldLoaders.end())
        {
            worldLoaders.erase(idx);
            removedWorldLoader = true;
        }
    }

    bool World::Initialize()
    {
        chunkProviderLoop.RunLoop();
        return true;
    }
    void World::Tick(float)
    {
        collectFulfilledChunkRequests();
        updateWorldLoaderChunks();
    }
    void World::Shutdown()
    {
        //Stop keeping chunks loaded!
        worldLoaders.clear();
        removedWorldLoader = true;
        //Force save all chunks, because now there is nothing keeping them alive!
        Tick(0);

        //This will save everything synchronously
        //For better performance, you really should get rid of the world loaders separately
        //So that this synchronous call can complete quickly
        chunkProviderLoop.StopLoop();
    }

    const char *World::name()
    {
        return "World";
    }

    __SelectorY World::operator[](int x)
    {
        return { x, this };
    }
    ITile *World::GetTileInfo(int tileX, int tileY, int tileZ)
    {
        auto chunk = getChunkFromTileCoords(tileX, tileZ);
        if (chunk == nullptr) return nullptr;
        return chunk->GetTileInfoGlobal(tileX, tileY, tileZ);
    }

    GlEngine::GraphicsObject *World::CreateGraphicsObject(GlEngine::GraphicsContext &ctx)
    {
        ctx;
        return nullptr;
    }
    void World::UpdateGraphicsObject(GlEngine::GraphicsContext &ctx, GlEngine::GraphicsObject *object)
    {
        GameObject::UpdateGraphicsObject(ctx, object);
    }

    bool World::initializeLoop()
    {
        return provider->Initialize();
    }
    void World::tickLoop(float)
    {
        static const unsigned MAX_REQUESTS = 256;
        static thread_local Vector<2, int> requests[MAX_REQUESTS];
        static thread_local Chunk *save_requests[MAX_REQUESTS];
        unsigned numRequests = 0, numSaveRequests = 0;
        {
            GlEngine::ScopedLock _lock(mutex);

            numSaveRequests = min(MAX_REQUESTS, chunkSaveRequests.size());
            for (size_t q = 0; q < numSaveRequests; q++)
                save_requests[q] = chunkSaveRequests[q];
            chunkSaveRequests.erase(chunkSaveRequests.begin(), chunkSaveRequests.begin() + numSaveRequests);

            numRequests = min(MAX_REQUESTS, chunkRequests.size());
            for (size_t q = 0; q < numRequests; q++)
                requests[q] = chunkRequests[q];
            chunkRequests.erase(chunkRequests.begin(), chunkRequests.begin() + numRequests);
        }

        static thread_local Chunk *fulfillments[MAX_REQUESTS];
        for (size_t q = 0; q < numSaveRequests; q++)
            provider->Put(save_requests[q]);
        for (size_t q = 0; q < numRequests; q++)
            fulfillments[q] = provider->Get(requests[q]);

        {
            GlEngine::ScopedLock _lock(mutex);
            for (size_t q = 0; q < numRequests; q++)
                chunkFulfillments.push_back(fulfillments[q]);
        }
    }
    void World::shutdownLoop()
    {
        GlEngine::ScopedLock _lock(mutex);
        while (chunkSaveRequests.size() != 0 || chunkRequests.size() != 0)
            tickLoop(0);
        provider->Shutdown();
    }

    void World::collectFulfilledChunkRequests()
    {
        GlEngine::ScopedLock _lock(mutex);
        for (size_t q = 0; q < chunkFulfillments.size(); q++)
        {
            auto newChunk = chunkFulfillments[q];
            auto oldChunk = getChunk(newChunk->GetX(), newChunk->GetZ());
            assert(oldChunk == nullptr || oldChunk == newChunk);
            loadedChunks.push_back(newChunk);
        }
        chunkFulfillments.clear();
    }

    void World::updateWorldLoaderChunks()
    {
        if (!requiresWorldLoaderUpdate()) return;
        removedWorldLoader = false;

        int minx, minz, maxx, maxz, directPrice;
        if (!getMinMaxChunkCoords(minx, minz, maxx, maxz, directPrice)) return;

        GlEngine::ScopedLock _lock(mutex);
        if ((maxx - minx) * (maxz - minz) > directPrice) updateWorldLoaderChunks_direct();
        else updateWorldLoaderChunks_rect(minx, maxx, minz, maxz);
    }
    void World::updateWorldLoaderChunks_direct()
    {
        for (size_t q = 0; q < worldLoaders.size(); q++)
        {
            auto wl = worldLoaders[0];
            auto tox = wl->GetX() + wl->GetWidth() + 1,
                 toz = wl->GetZ() + wl->GetDepth() + 1;
            for (int w = wl->GetX() - wl->GetWidth(); w < tox; w++)
                for (int e = wl->GetZ() - wl->GetDepth(); e < toz; e++)
                    updateWorldLoaderChunk(w, e);
        }
        for (size_t q = 0; q < loadedChunks.size(); q++)
        {
            auto chunk = loadedChunks[0];
            updateWorldLoaderChunk(chunk->GetX(), chunk->GetZ());
        }
    }
    void World::updateWorldLoaderChunks_rect(int minx, int maxx, int minz, int maxz)
    {
        for (int q = minx; q < maxx; q++)
            for (int w = minz; w < maxz; w++)
                updateWorldLoaderChunk(q, w);
    }
    void World::updateWorldLoaderChunk(int x, int z)
    {
        auto hint = getChunkLoadHint(x, z);
        if (hint == ChunkLoadHint::LoadAndAdd)
        {
            if (getChunk(x, z) != nullptr) return;
            if (std::find(chunkRequests.begin(), chunkRequests.end(), Vector<2, int> { x, z }) != chunkRequests.end()) return;
            chunkRequests.push_back({ x, z });
        }
        else if (hint == ChunkLoadHint::SaveAndRemove)
        {
            auto chunk = getChunk(x, z);
            if (chunk == nullptr) return;
            auto idx = std::find(loadedChunks.begin(), loadedChunks.end(), chunk);
            if (idx != loadedChunks.end()) loadedChunks.erase(idx);
            chunkSaveRequests.push_back(chunk);
        }
    }
    bool World::requiresWorldLoaderUpdate()
    {
        if (removedWorldLoader) return true;
        for (size_t q = 0; q < worldLoaders.size(); q++)
        {
            if (worldLoaders[q]->IsDirty()) return true;
        }
        return false;
    }
    bool World::getMinMaxChunkCoords(int &minx, int &maxx, int &minz, int &maxz, int &directPrice)
    {
        if (loadedChunks.size() == 0 && worldLoaders.size() == 0) return false;
        if (worldLoaders.size() != 0)
        {
            auto firstWorldLoader = worldLoaders[0];
            minx = firstWorldLoader->GetX() - firstWorldLoader->GetWidth();
            maxx = firstWorldLoader->GetX() + firstWorldLoader->GetWidth() + 1;
            minz = firstWorldLoader->GetZ() - firstWorldLoader->GetDepth();
            maxz = firstWorldLoader->GetZ() + firstWorldLoader->GetDepth() + 1;
        }
        else
        {
            auto firstChunk = loadedChunks[0];
            minx = firstChunk->GetX();
            maxx = firstChunk->GetX() + 1;
            minz = firstChunk->GetZ();
            maxz = firstChunk->GetZ() + 1;
        }

        directPrice = loadedChunks.size();
        for (size_t q = 0; q < worldLoaders.size(); q++)
        {
            auto wl = worldLoaders[0];
            minx = min(minx, wl->GetX() - wl->GetWidth());
            maxx = max(maxx, wl->GetX() + wl->GetWidth() + 1);
            minz = min(minz, wl->GetZ() - wl->GetDepth());
            maxz = max(maxz, wl->GetZ() + wl->GetDepth() + 1);
            directPrice += wl->GetWidth() * wl->GetDepth() * 4;
        }
        for (size_t q = 0; q < loadedChunks.size(); q++)
        {
            auto chunk = loadedChunks[0];
            minx = min(minx, chunk->GetX());
            maxx = max(maxx, chunk->GetX() + 1);
            minz = min(minz, chunk->GetZ());
            maxz = max(maxz, chunk->GetZ() + 1);
        }

        return true;
    }

    ChunkLoadHint World::getChunkLoadHint(int x, int z)
    {
        auto hint = ChunkLoadHint::SaveAndRemove;
        for (size_t q = 0; q < worldLoaders.size(); q++)
        {
            hint = max(hint, worldLoaders[q]->GetChunkLoadHint(x, z));
            if (hint == ChunkLoadHint::LoadAndAdd) break;
        }
        return hint;
    }
    Vector<2, int> World::getChunkCoordsFromTileCoords(int x, int z)
    {
        auto int_divide_floor = [](int a, int b) {
            return (a / b) - (a < 0 ? 1 : 0);
        };
        return {
            int_divide_floor(x, Chunk::TILES_PER_CHUNK_X),
            int_divide_floor(z, Chunk::TILES_PER_CHUNK_Z)
        };
    }
    Chunk *World::getChunkFromTileCoords(int x, int z)
    {
        return getChunk(getChunkCoordsFromTileCoords(x, z));
    }
    Chunk *World::getChunk(int chunkX, int chunkZ)
    {
        for (size_t q = 0; q < loadedChunks.size(); q++)
        {
            auto chunk = loadedChunks[q];
            if (chunk->GetX() == chunkX && chunk->GetZ() == chunkZ) return chunk;
        }
        return nullptr;
    }
}
