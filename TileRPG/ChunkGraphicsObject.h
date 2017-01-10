#pragma once

#include "VboGraphicsObject.h"
#include <unordered_map>
#include "RenderTargetLayer.h"
#include "VboType.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ShaderFactory;
    }

    class Texture;
    template <VboType type, typename... TArgs>
    class InstancedGraphicsObject;
}

namespace TileRPG
{
    class World;
    class Chunk;

    class ChunkGraphicsObject : public GlEngine::VboGraphicsObject
    {
    public:
        ChunkGraphicsObject(Chunk *chunk, World *world);
        ~ChunkGraphicsObject();
        
        bool Initialize() override;
        bool InitializeGraphics() override;

        void AddInstance(GlEngine::GraphicsObject *gobj, Matrix<4, 4> localTransformation);

        void PreRender(GlEngine::RenderTargetLayer layer) override;
        void RenderImpl(GlEngine::RenderTargetLayer layer) override;
        void PostRender(GlEngine::RenderTargetLayer layer) override;

        Matrix<4, 4> GetTransformation();

        const char *name() override;

        inline Chunk &GetChunk()
        {
            return *chunk;
        }
        inline World &GetWorld()
        {
            return *world;
        }

        inline unsigned GetUpdateVersion()
        {
            return version;
        }

    private:
        Chunk *chunk;
        World *world;
        unsigned version;

        typedef std::unordered_map<GraphicsObject*, GlEngine::InstancedGraphicsObject<GlEngine::VboType::Float, Matrix<4, 4>>*> instances_map_t;
        instances_map_t instances;
    };
}
