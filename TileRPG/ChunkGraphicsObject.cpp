#include "stdafx.h"
#include "ChunkGraphicsObject.h"
#include "Chunk.h"

#include "Texture.h"
#include "Shader.h"
#include "VBOFactory.h"
#include "MatrixStack.h"

namespace TileRPG
{
    ChunkGraphicsObject::ChunkGraphicsObject(Chunk *chunk, World *world)
        : VboGraphicsObject(
            GlEngine::Shader::Create("Shaders", "direct_light_tex"),
            GlEngine::Texture::FromFile("Textures/dirt.png")
          ),
          chunk(chunk), world(world)
    {
    }
    ChunkGraphicsObject::~ChunkGraphicsObject()
    {
    }

    bool ChunkGraphicsObject::Initialize()
    {
        transformationMatrix = Mat3T<float>::TranslateMatrix({ 
            chunk->GetX() * Chunk::TILES_PER_CHUNK_X,
            0,
            chunk->GetZ() * Chunk::TILES_PER_CHUNK_Z
        });

        verticesFactory = new GlEngine::VboFactory<GlEngine::VboType::Float, Vector<3>, Vector<2>, Vector<3>>(GlEngine::BufferMode::Array);
        trianglesFactory = new GlEngine::VboFactory<GlEngine::VboType::UnsignedShort, Vector<3, uint16_t>>(GlEngine::BufferMode::ElementArray);
        int elemIdx = 0;
        triCount = 0;

        auto maxy = chunk->GetMaxY();
        for (int x = 0; x < Chunk::TILES_PER_CHUNK_X; x++)
            for (int y = 0; y < maxy; y++)
                for (int z = 0; z < Chunk::TILES_PER_CHUNK_Z; z++)
                {
                    auto tile = chunk->GetTileInfo(x, y, z);
                    if (tile != 0)
                    {
                        if (x == 0 || chunk->GetTileInfo(x - 1, y, z) == 0)
                        {
                            //Render face Xm
                            verticesFactory->AddVertex({ x, y,     z },     { 0, 0 }, { -1, 0, 0 });
                            verticesFactory->AddVertex({ x, y + 1, z },     { 1, 0 }, { -1, 0, 0 });
                            verticesFactory->AddVertex({ x, y + 1, z + 1 }, { 1, 1 }, { -1, 0, 0 });
                            verticesFactory->AddVertex({ x, y,     z + 1 }, { 0, 1 }, { -1, 0, 0 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 1, elemIdx + 2 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 3 });
                            elemIdx += 4;
                            triCount += 2;
                        }
                        if (x == Chunk::TILES_PER_CHUNK_X - 1 || chunk->GetTileInfo(x + 1, y, z) == 0)
                        {
                            //Render face Xp
                            verticesFactory->AddVertex({ x + 1, y,     z },     { 0, 0 }, { 1, 0, 0 });
                            verticesFactory->AddVertex({ x + 1, y + 1, z },     { 1, 0 }, { 1, 0, 0 });
                            verticesFactory->AddVertex({ x + 1, y + 1, z + 1 }, { 1, 1 }, { 1, 0, 0 });
                            verticesFactory->AddVertex({ x + 1, y,     z + 1 }, { 0, 1 }, { 1, 0, 0 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 1 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 3, elemIdx + 2 });
                            elemIdx += 4;
                            triCount += 2;
                        }

                        if (y != 0 && chunk->GetTileInfo(x, y - 1, z) == 0)
                        {
                            //TODO: Do I really need Ym? Ever? This may just be wasted tris
                            //Render face Ym
                            verticesFactory->AddVertex({ x,     y, z },     { 0, 0 }, { 0, -1, 0 });
                            verticesFactory->AddVertex({ x + 1, y, z },     { 1, 0 }, { 0, -1, 0 });
                            verticesFactory->AddVertex({ x + 1, y, z + 1 }, { 1, 1 }, { 0, -1, 0 });
                            verticesFactory->AddVertex({ x,     y, z + 1 }, { 0, 1 }, { 0, -1, 0 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 1 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 3, elemIdx + 2 });
                            elemIdx += 4;
                            triCount += 2;
                        }
                        if (chunk->GetTileInfo(x, y + 1, z) == 0)
                        {
                            //Render face Yp
                            verticesFactory->AddVertex({ x,     y + 1, z },     { 0, 0 }, { 0, 1, 0 });
                            verticesFactory->AddVertex({ x + 1, y + 1, z },     { 1, 0 }, { 0, 1, 0 });
                            verticesFactory->AddVertex({ x + 1, y + 1, z + 1 }, { 1, 1 }, { 0, 1, 0 });
                            verticesFactory->AddVertex({ x,     y + 1, z + 1 }, { 0, 1 }, { 0, 1, 0 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 1, elemIdx + 2 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 3 });
                            elemIdx += 4;
                            triCount += 2;
                        }

                        if (z == 0 || chunk->GetTileInfo(x, y, z - 1) == 0)
                        {
                            //Render face Zm
                            verticesFactory->AddVertex({ x,     y,     z }, { 0, 0 }, { 0, 0, -1 });
                            verticesFactory->AddVertex({ x + 1, y,     z }, { 1, 0 }, { 0, 0, -1 });
                            verticesFactory->AddVertex({ x + 1, y + 1, z }, { 0, 1 }, { 0, 0, -1 });
                            verticesFactory->AddVertex({ x,     y + 1, z }, { 1, 1 }, { 0, 0, -1 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 1, elemIdx + 2 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 3 });
                            elemIdx += 4;
                            triCount += 2;
                        }
                        if (z == Chunk::TILES_PER_CHUNK_Z - 1 || chunk->GetTileInfo(x, y, z + 1) == 0)
                        {
                            //Render face Zp
                            verticesFactory->AddVertex({ x,     y,     z + 1 }, { 0, 0 }, { 0, 0, 1 });
                            verticesFactory->AddVertex({ x + 1, y,     z + 1 }, { 1, 0 }, { 0, 0, 1 });
                            verticesFactory->AddVertex({ x + 1, y + 1, z + 1 }, { 0, 1 }, { 0, 0, 1 });
                            verticesFactory->AddVertex({ x,     y + 1, z + 1 }, { 1, 1 }, { 0, 0, 1 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 1 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 3, elemIdx + 2 });
                            elemIdx += 4;
                            triCount += 2;
                        }
                    }
                }
        return true;
    }

    void ChunkGraphicsObject::Render()
    {
        GlEngine::MatrixStack::ModelView.mult(transformationMatrix);
        VboGraphicsObject::Render();
        GlEngine::MatrixStack::ModelView.pop();
    }
    
    const char *ChunkGraphicsObject::name()
    {
        return "ChunkGraphicsObject";
    }
}
