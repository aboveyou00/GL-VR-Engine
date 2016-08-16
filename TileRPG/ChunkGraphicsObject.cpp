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
    void ChunkGraphicsObject::Shutdown()
    {
        for (auto pair = instances.begin(); pair != instances.end(); pair++)
        {
            auto &gobj = *pair->first;
            auto &vec = pair->second;
            for (size_t q = 0; q < vec.size(); q++)
                gobj.RemoveInstance(vec[q]);
        }
    }

    void ChunkGraphicsObject::AddInstance(VboGraphicsObject<Matrix<4, 4>> *gobj, Matrix<4, 4> localTransformation)
    {
        auto index = gobj->AddInstance(GetTransformation() * localTransformation);
        instances[gobj].push_back(index);
    }

    void ChunkGraphicsObject::PreRender()
    {
        VboGraphicsObject::PreRender();
        GlEngine::MatrixStack::ModelView.mult(GetTransformation());
    }
    void ChunkGraphicsObject::PostRender()
    {
        GlEngine::MatrixStack::ModelView.pop();
        VboGraphicsObject::PostRender();
    }

    Matrix<4, 4> ChunkGraphicsObject::GetTransformation()
    {
        return Mat3T<float>::TranslateMatrix({
            chunk->GetX() * Chunk::TILES_PER_CHUNK_X,
            0,
            chunk->GetZ() * Chunk::TILES_PER_CHUNK_Z
        });
    }
    
    const char *ChunkGraphicsObject::name()
    {
        return "ChunkGraphicsObject";
    }
}
