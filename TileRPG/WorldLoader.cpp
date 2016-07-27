#include "stdafx.h"
#include "WorldLoader.h"
#include "World.h"

namespace TileRPG
{
    WorldLoader::WorldLoader(World *world)
        : world(world), dirty(false), position({ 0, 0 }), size({ 0, 0 })
    {
        if (world != nullptr) world->RegisterWorldLoader(this);
    }
    WorldLoader::~WorldLoader()
    {
        if (world != nullptr) world->ReleaseWorldLoader(this);
        world = nullptr;
    }

    void WorldLoader::Move(int x, int z)
    {
        Move({ x, z });
    }
    void WorldLoader::Move(Vector<2, int> pos)
    {
        if (this->position != pos)
        {
            if (this->size[0] * this->size[1] != 0) dirty = true;
            position = pos;
        }
    }
    void WorldLoader::Resize(int width, int depth)
    {
        Resize({ width, depth });
    }
    void WorldLoader::Resize(Vector<2, int> size)
    {
        if (this->size != size)
        {
            if (size[0] * size[1] != 0 || this->size[0] * this->size[1] != 0) dirty = true;
            this->size = size;
        }
    }

    ChunkLoadHint WorldLoader::GetChunkLoadHint(int x, int z)
    {
        if (x <= position[0] - (size[0] * 2)) return ChunkLoadHint::SaveAndRemove;
        if (x >= position[0] + (size[0] * 2)) return ChunkLoadHint::SaveAndRemove;
        if (z <= position[1] - (size[1] * 2)) return ChunkLoadHint::SaveAndRemove;
        if (z <= position[1] + (size[1] * 2)) return ChunkLoadHint::SaveAndRemove;
        if (x < position[0] - size[0]) return ChunkLoadHint::Indeterminate;
        if (x > position[0] + size[0]) return ChunkLoadHint::Indeterminate;
        if (z < position[1] - size[1]) return ChunkLoadHint::Indeterminate;
        if (z < position[1] + size[1]) return ChunkLoadHint::Indeterminate;
        return ChunkLoadHint::LoadAndAdd;
    }
}
