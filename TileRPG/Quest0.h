#pragma once

#include "Quest.h"

namespace TileRPG
{
    class Quest0 : public Quest
    {
    public:
        Quest0(PlayerObject *po);
        ~Quest0();

        void Tick(float) override;

        void HandleEvent(GlEngine::Events::Event &evt) override;

        std::string name() override;

        const char *PauseMessage() override;

    private:
        unsigned stage;
        PlayerObject *player;
    };
}
