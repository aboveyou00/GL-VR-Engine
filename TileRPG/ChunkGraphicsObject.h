#pragma once

#include "VboGraphicsObject.h"
#include <unordered_map>
#include "RenderTargetLayer.h"

namespace GlEngine
{
    class ShaderFactory;
    class Texture;
}

namespace TileRPG
{
    class World;
    class Chunk;

    class ChunkGraphicsObject : public GlEngine::VboGraphicsObject<>
    {
    public:
        ChunkGraphicsObject(Chunk *chunk, World *world);
        ~ChunkGraphicsObject();
        
        bool Initialize() override;
        void Shutdown() override;

        void AddInstance(VboGraphicsObject<Matrix<4, 4>> *gobj, Matrix<4, 4> localTransformation);
        
        void PreRender(GlEngine::RenderTargetLayer layer) override;
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

        std::unordered_map<VboGraphicsObject<Matrix<4, 4>>*, std::vector<int>> instances;
    };
}
