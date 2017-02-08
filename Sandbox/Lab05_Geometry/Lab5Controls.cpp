#include "stdafx.h"
#include "Lab5Controls.h"
#include "KeyboardEvent.h"
#include "LogUtils.h"
#include "MathUtils.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;

Lab5Controls::Lab5Controls()
    : LabControls()
{
}
Lab5Controls::~Lab5Controls()
{
}

unsigned Lab5Controls::wireframeThickness = 1;

void Lab5Controls::HandleEvent(Event &evt)
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

    if (!evt.IsHandled()) LabControls::HandleEvent(evt);
}

std::string Lab5Controls::name()
{
    return "Lab5Controls";
}
