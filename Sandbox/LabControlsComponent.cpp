#include "stdafx.h"
#include "LabControlsComponent.h"
#include "KeyboardEvent.h"
#include "LogUtils.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;

LabControlsComponent::LabControlsComponent()
    : GameComponent("LabControlsComponent"), controllingLight(nullptr), movementSpeed(2.f)
{
}
LabControlsComponent::~LabControlsComponent()
{
}

void LabControlsComponent::Tick(float delta)
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

void LabControlsComponent::HandleEvent(Event &evt)
{
    auto *kbdEvt = dynamic_cast<KeyboardEvent*>(&evt);
    if (kbdEvt != nullptr)
    {
        if (kbdEvt->type() == KeyboardEventType::KeyTyped)
        {
            if (kbdEvt->GetVirtualKeyCode() == VK_SPACE || kbdEvt->GetVirtualKeyCode() == VK_LETTER<'P'>())
            {
                LabControlsComponent::isPaused = !LabControlsComponent::isPaused;
                GlEngine::Util::Log(LabControlsComponent::isPaused ? "Pausing" : "Playing");
                evt.Handle();
            }

            if (kbdEvt->GetVirtualKeyCode() >= VK_LETTER<'0'>() && kbdEvt->GetVirtualKeyCode() < VK_LETTER<'8'>())
            {
                auto flags = kbdEvt->GetVirtualKeyCode() - VK_NUMPAD0;
                LabControlsComponent::rotateX = (flags & 0b001) != 0;
                LabControlsComponent::rotateY = (flags & 0b010) != 0;
                LabControlsComponent::rotateZ = (flags & 0b100) != 0;
                evt.Handle();
            }
        }

        if (kbdEvt->type() == GlEngine::Events::KeyboardEventType::KeyPressed) this->keysDown[kbdEvt->GetVirtualKeyCode()] = true;
        if (kbdEvt->type() == GlEngine::Events::KeyboardEventType::KeyReleased) this->keysDown[kbdEvt->GetVirtualKeyCode()] = false;
    }

    if (!evt.IsHandled()) GlEngine::GameComponent::HandleEvent(evt);
}

void LabControlsComponent::SetControllingLight(GlEngine::PointLightSource *light)
{
    this->controllingLight = light;
}

bool LabControlsComponent::isPaused = false;
bool LabControlsComponent::rotateX = true;
bool LabControlsComponent::rotateY = true;
bool LabControlsComponent::rotateZ = true;
