#include "stdafx.h"
#include "Lab5ControlsComponent.h"
#include "KeyboardEvent.h"
#include "LogUtils.h"
#include "MathUtils.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;

Lab5ControlsComponent::Lab5ControlsComponent()
    : LabControlsComponent()
{
}
Lab5ControlsComponent::~Lab5ControlsComponent()
{
}

float Lab5ControlsComponent::wireframeThickness = 1;

void Lab5ControlsComponent::HandleEvent(Event &evt)
{
    auto *kbdEvt = dynamic_cast<KeyboardEvent*>(&evt);
    if (kbdEvt != nullptr && kbdEvt->GetEventType() == KeyboardEventType::KeyTyped)
    {
        if (kbdEvt->GetVirtualKeyCode() == VK_SQUARE_BRACKET_RIGHT && this->wireframeThickness < 6)
        {
            this->wireframeThickness++;
            GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting wireframe thickness to %d", this->wireframeThickness);
            kbdEvt->Handle();
        }
        else if (kbdEvt->GetVirtualKeyCode() == VK_SQUARE_BRACKET_LEFT && this->wireframeThickness > 0)
        {
            this->wireframeThickness--;
            GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting wireframe thickness to %d", this->wireframeThickness);
            kbdEvt->Handle();
        }
    }

    if (!evt.IsHandled()) LabControlsComponent::HandleEvent(evt);
}
