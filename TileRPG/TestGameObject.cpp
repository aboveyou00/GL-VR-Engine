#include "stdafx.h"
#include "TestGameObject.h"

#include "KeyboardEvent.h"

namespace TileRPG
{
    TestGameObject::TestGameObject()
        : upPressed(0), downPressed(0), leftPressed(0), rightPressed(0)
    {
        RequireTick(true);
		timePassed = 0;
    }
    TestGameObject::~TestGameObject()
    {
    }

    bool TestGameObject::Initialize()
    {
        if (!GameObject::Initialize()) return false;

        return true;
    }
    void TestGameObject::Tick(float delta)
    {
        timePassed += delta;
        auto motionVector = Vector<3> { (leftPressed ? -1 : 0) + (rightPressed ? 1 : 0), (upPressed ? 1 : 0) + (downPressed ? -1 : 0), 0 };
        if (motionVector.LengthSquared() > 1) motionVector = motionVector.Normalized();
        position += motionVector * delta;
        //auto theta = timePassed;
        //position = Vector<3> { sin(theta) / 2, cos(theta) / 2, 1 };
    }

    void TestGameObject::HandleEvent(GlEngine::Events::Event &evt)
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
        }
    }
}
