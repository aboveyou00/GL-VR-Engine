#pragma once

#include "VboGraphicsObject.h"
#include <unordered_map>
#include "VboType.h"

namespace GlEngine
{
    class Shader;
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
        void Shutdown() override;

        void AddInstance(GlEngine::GraphicsObject *gobj, Matrix<4, 4> localTransformation);
        
        void PreRender() override;
        void PostRender() override;

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
