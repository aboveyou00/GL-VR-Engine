#include "stdafx.h"
#include "WorldEditorTargetObject.h"
#include "WorldEditorTargetGraphicsObject.h"

#include "World.h"
#include "WorldLoader.h"
#include "KeyboardEvent.h"
#include "Matrix.h"
#include "Chunk.h"

namespace TileRPG
{
    WorldEditorTargetObject::WorldEditorTargetObject(World *world)
        : loader(new WorldLoader(world))
    {
    }
    WorldEditorTargetObject::~WorldEditorTargetObject()
    {
        SafeDelete(loader);
    }

    const char *WorldEditorTargetObject::name()
    {
        return "WorldEditorTargetObject";
    }

    void WorldEditorTargetObject::HandleEvent(GlEngine::Events::Event &evt)
    {
        auto kbevt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
        if (kbevt == nullptr) return;
        if (kbevt->GetEventType() != GlEngine::Events::KeyboardEventType::KeyTyped) return;

        Vector<3> translation = { 0, 0, 0 };
        switch (kbevt->GetVirtualKeyCode())
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

            break;
        }

        position += translation;
        if (position[1] < 0) position = { position[0], 0, position[2] };
        loader->Move(Chunk::getChunkCoordsFromTileCoords((int)position[0], (int)position[2]));
        loader->Resize(Chunk::getChunkDimensionsFromTileDimensions(32, 32));
    }

    GlEngine::GraphicsObject *WorldEditorTargetObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
    {
        return new WorldEditorTargetGraphicsObject();
    }
}
