#pragma once

#include "VboGraphicsObject.h"

namespace GlEngine
{
    class Shader;
    class Texture;
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

        void PreRender() override;
        void PostRender() override;
        
        const char *name() override;

        inline Chunk &GetChunk()
        {
            return *chunk;
        }
        inline World &GetWorld()
        {
            return *world;
        }

    private:
        Matrix<4, 4> transformationMatrix;
        Chunk *chunk;
        World *world;
    };
}
