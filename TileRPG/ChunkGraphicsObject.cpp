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
            -3.5,
            chunk->GetZ() * Chunk::TILES_PER_CHUNK_Z
        });

        verticesFactory = new GlEngine::VboFactory<GlEngine::VboType::Float, Vector<3>, Vector<2>, Vector<3>>(GlEngine::BufferMode::Array);
        trianglesFactory = new GlEngine::VboFactory<GlEngine::VboType::UnsignedShort, Vector<3, uint16_t>>(GlEngine::BufferMode::ElementArray);
        int elemIdx = 0;
        triCount = 0;

        auto maxy = chunk->GetMaxY();
        for (int q = 0; q < Chunk::TILES_PER_CHUNK_X; q++)
            for (int w = 0; w < Chunk::TILES_PER_CHUNK_Z; w++)
                for (int e = 0; e < maxy; e++)
                {
                    auto tile = chunk->GetTileInfo(q, w, e);
                    if (tile != 0)
                    {
                        if (q == 0 || chunk->GetTileInfo(q - 1, w, e) == 0)
                        {
                            //Render face Xm
                            verticesFactory->AddVertex({ q, w,     e },     { 0, 0 }, { -1, 0, 0 });
                            verticesFactory->AddVertex({ q, w + 1, e },     { 1, 0 }, { -1, 0, 0 });
                            verticesFactory->AddVertex({ q, w + 1, e + 1 }, { 1, 1 }, { -1, 0, 0 });
                            verticesFactory->AddVertex({ q, w,     e + 1 }, { 0, 1 }, { -1, 0, 0 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 1, elemIdx + 2 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 3 });
                            elemIdx += 4;
                            triCount += 2;
                        }
                        if (q == Chunk::TILES_PER_CHUNK_X - 1 || chunk->GetTileInfo(q + 1, w, e) == 0)
                        {
                            //Render face Xp
                            verticesFactory->AddVertex({ q + 1, w,     e },     { 0, 0 }, { 1, 0, 0 });
                            verticesFactory->AddVertex({ q + 1, w + 1, e },     { 1, 0 }, { 1, 0, 0 });
                            verticesFactory->AddVertex({ q + 1, w + 1, e + 1 }, { 1, 1 }, { 1, 0, 0 });
                            verticesFactory->AddVertex({ q + 1, w,     e + 1 }, { 0, 1 }, { 1, 0, 0 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 1 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 3, elemIdx + 2 });
                            elemIdx += 4;
                            triCount += 2;
                        }

                        if (w != 0 && chunk->GetTileInfo(q, w - 1, e) == 0)
                        {
                            //TODO: Do I really need Ym? Ever? This may just be wasted tris
                            //Render face Ym
                            verticesFactory->AddVertex({ q,     w, e },     { 0, 0 }, { 0, -1, 0 });
                            verticesFactory->AddVertex({ q + 1, w, e },     { 1, 0 }, { 0, -1, 0 });
                            verticesFactory->AddVertex({ q + 1, w, e + 1 }, { 1, 1 }, { 0, -1, 0 });
                            verticesFactory->AddVertex({ q,     w, e + 1 }, { 0, 1 }, { 0, -1, 0 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 1 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 3, elemIdx + 2 });
                            elemIdx += 4;
                            triCount += 2;
                        }
                        if (chunk->GetTileInfo(q, w + 1, e) == 0)
                        {
                            //Render face Yp
                            verticesFactory->AddVertex({ q,     w + 1, e },     { 0, 0 }, { 0, 1, 0 });
                            verticesFactory->AddVertex({ q + 1, w + 1, e },     { 1, 0 }, { 0, 1, 0 });
                            verticesFactory->AddVertex({ q + 1, w + 1, e + 1 }, { 1, 1 }, { 0, 1, 0 });
                            verticesFactory->AddVertex({ q,     w + 1, e + 1 }, { 0, 1 }, { 0, 1, 0 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 1, elemIdx + 2 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 3 });
                            elemIdx += 4;
                            triCount += 2;
                        }

                        if (e == 0 || chunk->GetTileInfo(q, w, e - 1) == 0)
                        {
                            //Render face Zm
                            verticesFactory->AddVertex({ q,     w,     e }, { 0, 0 }, { 0, 0, -1 });
                            verticesFactory->AddVertex({ q + 1, w,     e }, { 1, 0 }, { 0, 0, -1 });
                            verticesFactory->AddVertex({ q + 1, w + 1, e }, { 0, 1 }, { 0, 0, -1 });
                            verticesFactory->AddVertex({ q,     w + 1, e }, { 1, 1 }, { 0, 0, -1 });

                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 1, elemIdx + 2 });
                            trianglesFactory->AddVertex({ elemIdx + 0, elemIdx + 2, elemIdx + 3 });
                            elemIdx += 4;
                            triCount += 2;
                        }
                        if (e == Chunk::TILES_PER_CHUNK_Z - 1 || chunk->GetTileInfo(q, w, e + 1) == 0)
                        {
                            //Render face Zp
                            verticesFactory->AddVertex({ q,     w,     e + 1 }, { 0, 0 }, { 0, 0, 1 });
                            verticesFactory->AddVertex({ q + 1, w,     e + 1 }, { 1, 0 }, { 0, 0, 1 });
                            verticesFactory->AddVertex({ q + 1, w + 1, e + 1 }, { 0, 1 }, { 0, 0, 1 });
                            verticesFactory->AddVertex({ q,     w + 1, e + 1 }, { 1, 1 }, { 0, 0, 1 });

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
