#pragma once

namespace GlEngine
{
    class ENGINE_SHARED IComponent
    {
        virtual bool Initialize() = 0;
        virtual void Shutdown() = 0;
    };
}
