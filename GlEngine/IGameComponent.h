#pragma once

#include "IComponent.h"

namespace GlEngine
{
    class IGameComponent : public IComponent
    {
        virtual void Tick(float delta) = 0;
    };
}
