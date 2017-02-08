#include "stdafx.h"
#include "Lab3Controls.h"
#include "KeyboardEvent.h"
#include "LogUtils.h"
#include "MathUtils.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;

Lab3Controls::Lab3Controls()
    : attenuationIdx(0), LabControls()
{
}
Lab3Controls::~Lab3Controls()
{
}

void Lab3Controls::HandleEvent(Event &evt)
{
    auto *kbdEvt = dynamic_cast<KeyboardEvent*>(&evt);
    if (kbdEvt != nullptr && kbdEvt->GetEventType() == KeyboardEventType::KeyTyped)
    {
        if (kbdEvt->GetVirtualKeyCode() == VK_PAGE_UP && this->celShadingSteps < 100)
        {
            this->celShadingSteps++;
            GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting cel shading steps to %d", this->celShadingSteps);
            kbdEvt->Handle();
        }
        else if (kbdEvt->GetVirtualKeyCode() == VK_PAGE_DOWN && this->celShadingSteps > 3)
        {
            this->celShadingSteps--;
            GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting cel shading steps to %d", this->celShadingSteps);
            kbdEvt->Handle();
        }
        else if (kbdEvt->GetVirtualKeyCode() == VK_SQUARE_BRACKET_LEFT && this->spotlightCutoffAngle > 0deg) {
            this->spotlightCutoffAngle -= (kbdEvt->IsShiftPressed() ? 10deg : 1deg);
            if (this->spotlightCutoffAngle < 0) this->spotlightCutoffAngle = 0;
            GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting spotlight cutoff angle to %ddeg", (unsigned)round(GlEngine::Util::radToDeg(this->spotlightCutoffAngle)));
            kbdEvt->Handle();
        }
        else if (kbdEvt->GetVirtualKeyCode() == VK_SQUARE_BRACKET_RIGHT && this->spotlightCutoffAngle < 90deg) {
            this->spotlightCutoffAngle += (kbdEvt->IsShiftPressed() ? 10deg : 1deg);
            if (this->spotlightCutoffAngle > 90) this->spotlightCutoffAngle = 90;
            GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting spotlight cutoff angle to %ddeg", (unsigned)round(GlEngine::Util::radToDeg(this->spotlightCutoffAngle)));
            kbdEvt->Handle();
        }
        else if (kbdEvt->GetVirtualKeyCode() == VK_FORWARD_SLASH)
        {
            attenuationIdx++;
            if (attenuationIdx >= ATTENTUATION_VALUE_COUNT) attenuationIdx = 0;
            this->spotlightAttenuation = attenuationValues[attenuationIdx];
            GlEngine::Util::Log(GlEngine::LogType::InfoC, "Setting spotlight attenuation to %f", this->spotlightAttenuation);
            kbdEvt->Handle();
        }
    }

    if (!evt.IsHandled()) LabControls::HandleEvent(evt);
}

std::string Lab3Controls::name()
{
    return "Lab3Controls";
}

unsigned Lab3Controls::celShadingSteps = 5;
float Lab3Controls::spotlightCutoffAngle = 30deg;
float Lab3Controls::spotlightAttenuation;

float Lab3Controls::attenuationValues[Lab3Controls::ATTENTUATION_VALUE_COUNT] = { 0.5f, 1.0f, 2.0f, 4.0f };
