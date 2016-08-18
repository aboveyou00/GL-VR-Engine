#include "stdafx.h"
#include "ChunkGraphicsObject.h"
#include "Chunk.h"
#include "ITile.h"
#include "TileManager.h"

#include "Texture.h"
#include "BlinnMaterial.h"
#include "VBOFactory.h"
#include "MatrixStack.h"
#include "InstancedGraphicsObject.h"

namespace TileRPG
{
    ChunkGraphicsObject::ChunkGraphicsObject(Chunk *chunk, World *world)
        : chunk(chunk),
          world(world),
          version(chunk->GetUpdateVersion()),
          instances()
    {
    }
    ChunkGraphicsObject::~ChunkGraphicsObject()
    {
    }

    bool ChunkGraphicsObject::Initialize()
    {
        auto texture = GlEngine::Texture::FromFile("Textures/dirt.png");
        auto mat = GlEngine::BlinnMaterial::Create(texture);
        SetMaterial(mat);

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
    }

    void ChunkGraphicsObject::AddInstance(GraphicsObject *gobj, Matrix<4, 4> localTransformation)
    {
        assert(!finalized);
        auto igo_ptr = instances[gobj];
        if (igo_ptr == nullptr) igo_ptr = instances[gobj] = new GlEngine::InstancedGraphicsObject<GlEngine::VboType::Float, Matrix<4, 4>>(gobj);
        auto &igo = *igo_ptr;

        igo.AddInstance(GetTransformation() * localTransformation);
    }

    void ChunkGraphicsObject::PreRender(GlEngine::RenderTargetLayer layer)
    {
        VboGraphicsObject::PreRender(layer);
        GlEngine::MatrixStack::ModelView.mult(GetTransformation());
    }
    void ChunkGraphicsObject::PostRender(GlEngine::RenderTargetLayer layer)
    {
        GlEngine::MatrixStack::ModelView.pop();
        VboGraphicsObject::PostRender(layer);
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
