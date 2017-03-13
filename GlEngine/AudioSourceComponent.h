#pragma once

#include "GameComponent.h"

namespace GlEngine
{
    class IAudioSource;

    class ENGINE_SHARED AudioSourceComponent : public GameComponent
    {
    public:
        AudioSourceComponent(std::string name, std::string source = ""s);
        ~AudioSourceComponent();

        virtual void Tick(float delta) override;

        IAudioSource *source();

    private:
        IAudioSource *_source;
    };
}
