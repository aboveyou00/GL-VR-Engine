#pragma once

#include "IComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED IGraphicsComponent : public IComponent
    {
    public:
        virtual bool InitializeGraphics() = 0;
        virtual void ShutdownGraphics() = 0;

        virtual operator bool() = 0;
    };
}
