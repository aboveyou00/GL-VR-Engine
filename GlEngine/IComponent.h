#pragma once

namespace GlEngine
{
    class IComponent
    {
        virtual bool Initialize() = 0;
        virtual void Shutdown() = 0;
    };
}
