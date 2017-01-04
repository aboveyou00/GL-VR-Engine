#include "stdafx.h"
#include "TestEventObject.h"

#include "KeyboardEvent.h"

#include "Engine.h"
#include "AudioController.h"
#include "GraphicsObject.h"
#include "GraphicsContext.h"

#include "ObjGraphicsObject.h"
#include "FbxGraphicsObject.h"

#include "WorldLoader.h"
#include "Chunk.h"

namespace TileRPG
{
    TestEventObject::TestEventObject(World *world)
        : upPressed(0), downPressed(0),
        leftPressed(0), rightPressed(0),
        inPressed(0), outPressed(0),
        loader(new WorldLoader(world))
    {
        RequireTick(true);
        timePassed = 0;
    }
    TestEventObject::~TestEventObject()
    {
        if (loader != nullptr)
        {
            delete loader;
            loader = nullptr;
        }
    }

    void TestEventObject::Tick(float delta)
    {
        timePassed += delta;
        auto motionVector = Vector<3> { (leftPressed ? 1 : 0) + (rightPressed ? -1 : 0), (upPressed ? 1 : 0) + (downPressed ? -1 : 0), (outPressed ? 1 : 0) + (inPressed ? -1 : 0) };
        if (motionVector.LengthSquared() > 0.5) motionVector = motionVector.Normalized(5);
        position += motionVector * delta;
        //auto theta = timePassed;
        //position = Vector<3> { sin(theta) / 2, cos(theta) / 2, 1 };

        auto &audioCtrl = GlEngine::Engine::GetInstance().GetAudioController();
        audioCtrl.SetListenerPosition(position);

        loader->Move(Chunk::getChunkCoordsFromTileCoords((int)position[0], (int)position[1]));
        loader->Resize(Chunk::getChunkDimensionsFromTileDimensions(32, 32));
    }

    const char *TestEventObject::name()
    {
        return "TestEventObject";
    }

    void TestEventObject::HandleEvent(GlEngine::Events::Event &evt)
    {
        auto kbevt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
        if (kbevt == nullptr) return;
        if (kbevt->GetEventType() != GlEngine::Events::KeyboardEventType::KeyPressed && kbevt->GetEventType() != GlEngine::Events::KeyboardEventType::KeyReleased) return;
        auto pressed = kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyPressed;
        switch (kbevt->GetVirtualKeyCode())
        {
        case VK_UP:
            upPressed = pressed;
            break;
        case VK_DOWN:
            downPressed = pressed;
            break;
        case VK_LEFT:
            leftPressed = pressed;
            break;
        case VK_RIGHT:
            rightPressed = pressed;
            break;
        case VK_LETTER<'q'>():
            inPressed = pressed;
            break;
        case VK_LETTER<'a'>():
            outPressed = pressed;
        }
    }

    GlEngine::GraphicsObject *TestEventObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
    {
        return GlEngine::FbxGraphicsObject<>::Create("test.fbx");
        //return GlEngine::ObjGraphicsObject::Create("Resources/suzanne.obj", "Shaders", "direct_light_tex", "Textures/checkers.png");
    }
}
