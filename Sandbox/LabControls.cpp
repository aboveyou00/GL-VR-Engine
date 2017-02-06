#include "stdafx.h"
#include "LabControls.h"
#include "KeyboardEvent.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;

LabControls::LabControls()
    : movementSpeed(2.f), controllingLight(nullptr)
{
    RequireTick(true);
}
LabControls::~LabControls()
{
}

void LabControls::Tick(float delta)
{
    auto translation = Vector<3> { 0, 0, 0 };

    if (this->keysDown[VK_LETTER<'w'>()]) translation += { 0, 0, 1 };
    if (this->keysDown[VK_LETTER<'s'>()]) translation += { 0, 0, -1 };
    if (this->keysDown[VK_LETTER<'a'>()]) translation += { -1, 0, 0 };
    if (this->keysDown[VK_LETTER<'d'>()]) translation += { 1, 0, 0 };
    if (this->keysDown[VK_LETTER<'q'>()]) translation += { 0, -1, 0 };
    if (this->keysDown[VK_LETTER<'e'>()]) translation += { 0, 1, 0 };
    translation *= delta * movementSpeed;
    if ((GetKeyState(VK_SHIFT) & 0b10000000) != 0) translation *= 4;

    if (controllingLight != nullptr) controllingLight->SetPosition(controllingLight->position() + translation);
}

void LabControls::HandleEvent(Event &evt)
{
    auto *kbdEvt = dynamic_cast<KeyboardEvent*>(&evt);
    if (kbdEvt != nullptr)
    {
        if (kbdEvt->GetEventType() == KeyboardEventType::KeyTyped)
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

        if (kbdEvt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyPressed) this->keysDown[kbdEvt->GetVirtualKeyCode()] = true;
        if (kbdEvt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyReleased) this->keysDown[kbdEvt->GetVirtualKeyCode()] = false;
    }

    if (!evt.IsHandled()) GlEngine::GameObject::HandleEvent(evt);
}

const char *LabControls::name()
{
    return "LabControls";
}

GlEngine::GraphicsObject *LabControls::CreateGraphicsObject(GlEngine::GraphicsContext*)
{
    return nullptr;
}

void LabControls::SetControllingLight(GlEngine::PointLightSource *light)
{
    this->controllingLight = light;
}

bool LabControls::isPaused = false;
bool LabControls::rotateX = true;
bool LabControls::rotateY = true;
bool LabControls::rotateZ = true;
