#include "stdafx.h"
#include "Quest0.h"
#include "PlayerObject.h"
#include "KeyboardEvent.h"
#include "DialogBoxObject.h"

namespace TileRPG
{

    Quest0::Quest0(PlayerObject *po)
        : stage(0), player(po)
    {
    }
    Quest0::~Quest0()
    {
    }

    void Quest0::Tick(float)
    {
        if (stage == 1 || stage == 7)
        {
            auto pos = player->position;
            if (pos[0] > -2 && pos[0] < 2 && pos[2] > -2) stage++;
        }
        else if (stage == 5)
        {
            auto pos = player->position;
            if (pos[0] < -15) stage++;
        }
        else if (stage == 10)
        {
            player->actor()->body->position = { 0, player->position[1], 5 };
            stage++;
        }
        auto dbo = this->GetDialogBoxObject();
        if (dbo != nullptr) dbo->SetTextureSource(PauseMessage());
    }

    void Quest0::HandleEvent(GlEngine::Events::Event &evt)
    {
        if (evt.IsHandled()) return;
        if (!IsPaused()) return;

        auto kbevt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
        if (kbevt == nullptr) return;
        if (kbevt->GetEventType() != GlEngine::Events::KeyboardEventType::KeyPressed &&
            kbevt->GetEventType() != GlEngine::Events::KeyboardEventType::KeyReleased) return;

        auto pressed = kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyReleased;
        switch (kbevt->GetVirtualKeyCode())
        {
        case VK_SPACE:
            if (!pressed) stage++;
            kbevt->Handle();
            break;
        }
    }

    std::string Quest0::name()
    {
        return "Quest0";
    }

    const char *Quest0::PauseMessage()
    {
        if (stage == 0) return "Textures/Quest0/wakeup.png";
        if (stage == 2) return "Textures/Quest0/guards0.png";
        if (stage == 3) return "Textures/Quest0/you0.png";
        if (stage == 4) return "Textures/Quest0/guards1.png";
        if (stage == 6) return "Textures/Quest0/foundherb.png";
        if (stage == 8) return "Textures/Quest0/you1.png";
        if (stage == 9) return "Textures/Quest0/guards2.png";
        return nullptr;
    }

    /*
    States:
    0: Wake up message
    1: Walk to guards
    2: Guards speak
    3: You speak
    4: Guards speak
    5: You go to find the herb
    6: Found herb message
    7: You go to find the guards
    8: You speak to the guards
    9: They speak back to you
    10: Quest complete!
    */
}
