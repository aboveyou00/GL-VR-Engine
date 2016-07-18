#include "stdafx.h"
#include "TestEventObject.h"

#include "KeyboardEvent.h"

#include "Engine.h"
#include "AudioController.h"
#include "GraphicsObject.h"
#include "GraphicsContext.h"

#include "ObjGraphicsObject.h"

namespace TileRPG
{
    TestEventObject::TestEventObject()
        : upPressed(0), downPressed(0), leftPressed(0), rightPressed(0), inPressed(0), outPressed(0)
    {
        RequireTick(true);
		timePassed = 0;
    }
    TestEventObject::~TestEventObject()
    {
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
        return GlEngine::ObjGraphicsObject::Create("suzanne.obj", "Shaders", "direct_light"/*, "Textures/checkers.png" */);
    }
}
