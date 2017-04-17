#include "stdafx.h"
#include "Lab9ControlsComponent.h"
#include "KeyboardEvent.h"
#include "LogUtils.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;

Lab9ControlsComponent::Lab9ControlsComponent()
    : displayDebugString(false), rayTracingEnabled(true)
{
}
Lab9ControlsComponent::~Lab9ControlsComponent()
{
}

void Lab9ControlsComponent::HandleEvent(Event &evt)
{
    auto *kbdEvt = dynamic_cast<KeyboardEvent*>(&evt);
    if (kbdEvt != nullptr && kbdEvt->type() == KeyboardEventType::KeyTyped)
    {
        if (kbdEvt->GetVirtualKeyCode() == VK_ALPHANUMERIC<'G'>())
        {
            this->displayDebugString = !this->displayDebugString;
            if (this->displayDebugString) GlEngine::Util::Log(GlEngine::LogType::InfoC, "Enabling debug string.");
            else GlEngine::Util::Log(GlEngine::LogType::InfoC, "Disabling debug string.");
            kbdEvt->Handle();
        }
        else if (kbdEvt->GetVirtualKeyCode() == VK_ALPHANUMERIC<'R'>())
        {
            this->rayTracingEnabled = !this->rayTracingEnabled;
            if (this->rayTracingEnabled) GlEngine::Util::Log(GlEngine::LogType::InfoC, "Enabling raytracing.");
            else GlEngine::Util::Log(GlEngine::LogType::InfoC, "Disabling raytracing.");
            kbdEvt->Handle();
        }
    }

    if (!evt.IsHandled()) LabControlsComponent::HandleEvent(evt);
}
