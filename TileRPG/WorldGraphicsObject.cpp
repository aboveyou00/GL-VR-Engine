#include "stdafx.h"
#include "WorldGraphicsObject.h"
#include "ChunkGraphicsObject.h"
#include "World.h"
#include "Chunk.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ResourceLoader.h"

namespace TileRPG
{
    WorldGraphicsObject::WorldGraphicsObject(World *world)
        : world(world)
    {
    }
    WorldGraphicsObject::~WorldGraphicsObject()
    {
    }

    bool WorldGraphicsObject::Initialize()
    {
        return true;
    }
    void WorldGraphicsObject::Shutdown()
    {
    }
    bool WorldGraphicsObject::InitializeGraphics()
    {
        return true;
    }
    void WorldGraphicsObject::ShutdownGraphics()
    {
    }

    void WorldGraphicsObject::UpdateChunks(std::vector<Chunk*> *chunks)
    {
        removeOldChunks(*chunks);
        addNewChunks(*chunks);
    }

    void WorldGraphicsObject::RenderImpl(GlEngine::RenderTargetLayer layer)
    {
        layer;
        //if (layer != GlEngine::RenderTargetLayer::Layer3dOpaque)
        //    return;

        for (auto ptr = chunkGraphics.begin(); ptr != chunkGraphics.end(); ptr++)
        {
            auto gobj = ptr->second;
            if (!gobj) continue;

            gobj->Render(layer);
        }
    }

    const char *WorldGraphicsObject::name()
    {
        return "WorldGraphicsObject";
    }
    WorldGraphicsObject::operator bool()
    {
        return true;
    }

    void WorldGraphicsObject::removeOldChunks(std::vector<Chunk*> &chunks)
    {
        std::vector<std::pair<Chunk*, ChunkGraphicsObject*>> toRemove;
        for (auto ptr = chunkGraphics.begin(); ptr != chunkGraphics.end(); ptr++)
        {
            auto differentVersions = ptr->second != nullptr && ptr->first->GetUpdateVersion() != ptr->second->GetUpdateVersion();
            auto deloaded = differentVersions || std::find(chunks.begin(), chunks.end(), ptr->first) == chunks.end();
            if (differentVersions || deloaded) toRemove.push_back(*ptr);
        }
        for (size_t q = 0; q < toRemove.size(); q++)
        {
            chunkGraphics.erase(toRemove[q].first);
            auto gobj = toRemove[q].second;

            if (gobj != nullptr)
            {
                auto resources = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ResourceLoader>();
                resources->QueueShutdown(gobj);
            }
        }
    }
    void WorldGraphicsObject::addNewChunks(std::vector<Chunk*> &chunks)
    {
        for (size_t q = 0; q < chunks.size(); q++)
        {
            auto chunk = chunks[q];
            auto gobj = chunkGraphics[chunk];
            if (gobj == nullptr)
            {
                if (!shouldRenderChunk(chunks, chunk)) continue;
                chunkGraphics[chunk] = new ChunkGraphicsObject(chunk, world);
            }
            else
            {
                //TODO: Check for dirty chunks, refresh if necessary
            }
        }
    }

    bool WorldGraphicsObject::shouldRenderChunk(std::vector<Chunk*>& chunks, Chunk *chunk)
    {
        auto x = chunk->GetX(),
             z = chunk->GetZ();
        return hasChunkAt(chunks, x - 1, z - 1) &&
               hasChunkAt(chunks, x,     z - 1) &&
               hasChunkAt(chunks, x + 1, z - 1) &&
               hasChunkAt(chunks, x - 1, z)     &&
               hasChunkAt(chunks, x + 1, z)     &&
               hasChunkAt(chunks, x - 1, z + 1) &&
               hasChunkAt(chunks, x,     z + 1) &&
               hasChunkAt(chunks, x + 1, z + 1);
    }
    bool WorldGraphicsObject::hasChunkAt(std::vector<Chunk*>& chunks, int x, int z)
    {
        for (size_t q = 0; q < chunks.size(); q++)
        {
            auto chunk = chunks[q];
            if (chunk->GetX() == x && chunk->GetZ() == z) return true;
        }
        return false;
    }
}
