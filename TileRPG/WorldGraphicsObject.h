#pragma once

#include "GraphicsObject.h"
#include <unordered_map>

namespace TileRPG
{
    class World;
    class Chunk;
    class ChunkGraphicsObject;

    class WorldGraphicsObject : public GlEngine::GraphicsObject
    {
    public:
        WorldGraphicsObject(World *world);
        ~WorldGraphicsObject();

        bool Initialize() override;
        void Shutdown() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

        void RenderImpl() override;
        void RenderInstancedImpl(unsigned instanceCount) override;

        operator bool() override;

        const char *name() override;

        void UpdateChunks(std::vector<Chunk*> *chunks);

    private:
        World *world;
        std::unordered_map<Chunk*, ChunkGraphicsObject*> chunkGraphics;

        void removeOldChunks(std::vector<Chunk*> &chunks);
        void addNewChunks(std::vector<Chunk*> &chunks);

        bool shouldRenderChunk(std::vector<Chunk*> &chunks, Chunk *chunk);
        bool hasChunkAt(std::vector<Chunk*> &chunks, int x, int z);
    };
}
