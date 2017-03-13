#pragma once

#include "GameComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED AudioListenerComponent : public GameComponent
    {
    public:
        AudioListenerComponent(std::string name = ""s);
        ~AudioListenerComponent();

        virtual void Tick(float delta) override;
    };
}
