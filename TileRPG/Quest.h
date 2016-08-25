#pragma once

#include "IGameComponent.h"

namespace GlEngine
{
    namespace Events
    {
        class Event;
    }
}

namespace TileRPG
{
    class PlayerObject;
    class DialogBoxObject;

    class Quest : public GlEngine::IGameComponent
    {
    public:
        Quest();
        ~Quest();

        static Quest *FirstQuest(PlayerObject *po);
        
        bool Initialize() override;
        void Tick(float delta) override = 0;
        void Shutdown() override;

        virtual bool IsPaused();
        virtual const char *PauseMessage() = 0;
        virtual void HandleEvent(GlEngine::Events::Event &evt) = 0;

        void SetDialogBoxObject(DialogBoxObject *dbo);
        DialogBoxObject *GetDialogBoxObject();

    private:
        DialogBoxObject *dbo;
    };
}
