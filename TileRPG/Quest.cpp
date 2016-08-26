#include "stdafx.h"
#include "Quest.h"
#include "Quest0.h"

namespace TileRPG
{
    Quest::Quest()
    {
    }
    Quest::~Quest()
    {
    }

    Quest *Quest::FirstQuest(PlayerObject *po)
    {
        return new Quest0(po);
    }

    bool Quest::Initialize()
    {
        return true;
    }
    void Quest::Shutdown()
    {
    }

    bool Quest::IsPaused()
    {
        return PauseMessage() != nullptr;
    }

    void Quest::SetDialogBoxObject(DialogBoxObject *dbo)
    {
        this->dbo = dbo;
    }
    DialogBoxObject *Quest::GetDialogBoxObject()
    {
        return dbo;
    }
}
