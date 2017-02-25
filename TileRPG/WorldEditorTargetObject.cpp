#include "stdafx.h"
#include "WorldEditorTargetObject.h"
#include "WorldEditorTargetGraphicsObject.h"

#include "World.h"
#include "WorldLoader.h"
#include "KeyboardEvent.h"
#include "Matrix.h"
#include "Chunk.h"

#include "AirTile.h"
#include "WaterTile.h"
#include "DirtTile.h"
#include "RockTile.h"
#include "CastleWallTile.h"
#include "CastleStairsTile.h"
#include "SolidAirTile.h"

namespace TileRPG
{
    WorldEditorTargetObject::WorldEditorTargetObject(World *world)
        : loader(new WorldLoader(world)), world(world)
    {
    }
    WorldEditorTargetObject::~WorldEditorTargetObject()
    {
        SafeDelete(loader);
    }

    std::string WorldEditorTargetObject::name()
    {
        return "WorldEditorTargetObject";
    }

    static const int TILE_IDS[] = {
        AirTile::GetInstance().GetTileId(),
        DirtTile::GetInstance().GetTileId(),
        RockTile::GetInstance().GetTileId(),
        WaterTile::GetInstance().GetTileId(),
        CastleWallTile::GetInstance().GetTileId(),
        CastleStairsTile::GetInstance().GetTileId(),
        SolidAirTile::GetInstance().GetTileId()
    };
    static const unsigned MAX_TILE_IDS = sizeof(TILE_IDS) / sizeof(int);

    void WorldEditorTargetObject::HandleEvent(GlEngine::Events::Event &evt)
    {
        auto kbevt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
        if (kbevt == nullptr) return;
        if (kbevt->type() != GlEngine::Events::KeyboardEventType::KeyTyped) return;

        Vector<3> translation = { 0, 0, 0 };
        auto vkcode = kbevt->GetVirtualKeyCode();
        int idx = -1;
        int info;
        switch (vkcode)
        {
        case VK_UP:
            translation += { 0, 0, 1 };
            break;
        case VK_DOWN:
            translation += { 0, 0, -1 };
            break;
        case VK_LEFT:
            translation += { -1, 0, 0 };
            break;
        case VK_RIGHT:
            translation += { 1, 0, 0 };
            break;
        case VK_LETTER<'q'>():
            translation += { 0, -1, 0 };
            break;
        case VK_LETTER<'a'>():
            translation += { 0, 1, 0 };
            break;

        case VK_SPACE:
        case VK_RETURN:
            info = world->GetTileInfo((int)position[0], (int)position[1], (int)position[2]);
            for (size_t q = 0; q < MAX_TILE_IDS; q++)
                if (TILE_IDS[q] == info)
                {
                    idx = q;
                    break;
                }
            idx++;
            if (idx >= MAX_TILE_IDS) idx = 0;
            world->SetTileInfo((int)position[0], (int)position[1], (int)position[2], TILE_IDS[idx]);
            break;

        case VK_NUMPAD0:
        case VK_NUMPAD1:
        case VK_NUMPAD2:
        case VK_NUMPAD3:
        case VK_NUMPAD4:
        case VK_NUMPAD5:
        case VK_NUMPAD6:
        case VK_NUMPAD7:
        case VK_NUMPAD8:
        case VK_NUMPAD9:
            idx = kbevt->GetVirtualKeyCode() - 0x61;
            if (kbevt->GetVirtualKeyCode() == VK_NUMPAD0) idx = 0x6a - 0x61;
            if (idx < MAX_TILE_IDS) world->SetTileInfo((int)position[0], (int)position[1], (int)position[2], TILE_IDS[idx]);
            break;
        }

        position += translation;
        if (position[1] < 0) position = { position[0], 0, position[2] };
        loader->Move(Chunk::getChunkCoordsFromTileCoords((int)position[0], (int)position[2]));
        loader->Resize(Chunk::getChunkDimensionsFromTileDimensions(32, 32));
    }

    GlEngine::GraphicsObject *WorldEditorTargetObject::CreateGraphicsObject(GlEngine::GraphicsContext*)
    {
        return new WorldEditorTargetGraphicsObject();
    }
}
