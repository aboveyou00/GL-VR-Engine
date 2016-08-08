#include "stdafx.h"
#include "ChunkGraphicsObject.h"
#include "Chunk.h"
#include "ITile.h"

#include "Texture.h"
#include "Shader.h"
#include "VBOFactory.h"
#include "MatrixStack.h"

#include "TileManager.h"

namespace TileRPG
{
    ChunkGraphicsObject::ChunkGraphicsObject(Chunk *chunk, World *world)
        : chunk(chunk), world(world), version(chunk->GetUpdateVersion())
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

        auto shader = GlEngine::Shader::Create("Shaders", "direct_light_tex");
        auto texture = GlEngine::Texture::FromFile("Textures/dirt.png");
        SetGraphics(shader, texture);

        auto &tileManager = TileManager::GetInstance();
        
        ITile *lastITile = nullptr;
        unsigned lastTile = 0;

        auto maxy = chunk->GetMaxY();
        for (int x = 0; x < Chunk::TILES_PER_CHUNK_X; x++)
            for (int z = 0; z < Chunk::TILES_PER_CHUNK_Z; z++)
                for (int y = 0; y < maxy; y++)
                {
                    auto tile = chunk->GetTileInfo(x, y, z);
                    if (tile == 0) continue;

                    if (lastTile != tile)
                    {
                        lastITile = tileManager.GetTile(tile);
                        lastTile = tile;
                    }

                    if (lastITile == nullptr) continue;

                    lastITile->AddToChunkGraphicsObject(*this, x, y, z);
                }

        return true;
    }

    void ChunkGraphicsObject::PreRender()
    {
        VboGraphicsObject::PreRender();
        GlEngine::MatrixStack::ModelView.mult(transformationMatrix);
    }
    void ChunkGraphicsObject::PostRender()
    {
        GlEngine::MatrixStack::ModelView.pop();
        VboGraphicsObject::PostRender();
    }
    
    const char *ChunkGraphicsObject::name()
    {
        return "ChunkGraphicsObject";
    }
}
