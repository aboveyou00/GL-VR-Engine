#pragma once

#include "GameObject.h"
#include "IChunkProvider.h"
#include "GameLoop.h"
#include "ITile.h"
#include "World_SelectorY.h"
#include "ChunkLoadHint.h"

namespace TileRPG
{
    class WorldLoader;

    class World : GlEngine::GameObject
    {
    public:
        World(IChunkProvider *provider);
        ~World();

        void RegisterWorldLoader(WorldLoader *loader);
        void ReleaseWorldLoader(WorldLoader *loader);

        bool Initialize() override;
        void Tick(float delta) override;
        void Shutdown() override;

        virtual const char *name() override;

        __SelectorY operator[](int x);
        ITile *GetTileInfo(int tileX, int tileY, int tileZ);

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;
        void UpdateGraphicsObject(GlEngine::GraphicsContext &ctx, GlEngine::GraphicsObject *object) override;

    private:
        IChunkProvider *provider;
        bool removedWorldLoader;
        std::vector<WorldLoader*> worldLoaders;
        std::vector<Chunk*> loadedChunks;

        GlEngine::GameLoop chunkProviderLoop;
        std::vector<Vector<2, int>> chunkRequests;
        std::vector<Chunk*> chunkSaveRequests, chunkFulfillments;

        rt_mutex mutex;

        bool initializeLoop();
        void tickLoop(float delta);
        void shutdownLoop();
        
        void collectFulfilledChunkRequests();

        void updateWorldLoaderChunks();
        void updateWorldLoaderChunks_direct();
        void updateWorldLoaderChunks_rect(int minx, int maxx, int minz, int maxz);
        void updateWorldLoaderChunk(int x, int z);
        bool requiresWorldLoaderUpdate();
        bool getMinMaxChunkCoords(int &minx, int &maxx, int &minz, int &maxz, int &directPrice);

        inline ChunkLoadHint getChunkLoadHint(Vector<2, int> xz)
        {
            return getChunkLoadHint(xz[0], xz[1]);
        }
        inline Vector<2, int> getChunkCoordsFromTileCoords(Vector<2, int> xz)
        {
            return getChunkCoordsFromTileCoords(xz[0], xz[1]);
        }
        inline Chunk *getChunkFromTileCoords(Vector<2, int> xz)
        {
            return getChunkFromTileCoords(xz[0], xz[1]);
        }
        inline Chunk *getChunk(Vector<2, int> xz)
        {
            return getChunk(xz[0], xz[1]);
        }

        ChunkLoadHint getChunkLoadHint(int x, int z);
        Vector<2, int> getChunkCoordsFromTileCoords(int x, int z);
        Chunk *getChunkFromTileCoords(int x, int z);
        Chunk *getChunk(int chunkX, int chunkZ);
    };
}
