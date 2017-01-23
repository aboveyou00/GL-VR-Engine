#include "stdafx.h"
#include "LabControls.h"
#include "KeyboardEvent.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;

LabControls::LabControls()
{
    RequireTick(true);
}
LabControls::~LabControls()
{
}

void LabControls::HandleEvent(Event &evt)
{
    auto *kbdEvt = dynamic_cast<KeyboardEvent*>(&evt);
    if (kbdEvt != nullptr && kbdEvt->GetEventType() == KeyboardEventType::KeyTyped)
    {
        if (kbdEvt->GetVirtualKeyCode() == VK_SPACE || kbdEvt->GetVirtualKeyCode() == VK_LETTER<'P'>())
        {
            LabControls::isPaused = !LabControls::isPaused;
            evt.Handle();
        }

        if (kbdEvt->GetVirtualKeyCode() >= VK_LETTER<'0'>() && kbdEvt->GetVirtualKeyCode() < VK_LETTER<'8'>())
        {
            auto flags = kbdEvt->GetVirtualKeyCode() - VK_NUMPAD0;
            LabControls::rotateX = (flags & 0b001) != 0;
            LabControls::rotateY = (flags & 0b010) != 0;
            LabControls::rotateZ = (flags & 0b100) != 0;
            evt.Handle();
        }
    }

    if (!evt.IsHandled()) GlEngine::GameObject::HandleEvent(evt);
}

const char *LabControls::name()
{
    return "LabControls";
}

GlEngine::GraphicsObject *LabControls::CreateGraphicsObject(GlEngine::GraphicsContext&)
{
    return nullptr;
}

bool LabControls::isPaused = false;
bool LabControls::rotateX = true;
bool LabControls::rotateY = true;
bool LabControls::rotateZ = true;
