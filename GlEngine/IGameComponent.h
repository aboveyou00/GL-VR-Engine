#pragma once

#include "IComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED IGameComponent : public IComponent
    {
        virtual void Tick(float delta) = 0;
    };
}
