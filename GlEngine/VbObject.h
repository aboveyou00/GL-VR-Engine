#pragma once

#include "IComponent.h"
#include "BufferMode.h"

namespace GlEngine
{
    struct ENGINE_SHARED VbObject : IComponent
    {
    public:
        VbObject();
        VbObject(unsigned buff, BufferMode mode);
        ~VbObject();

        bool Initialize();
        void Shutdown();

        void MakeCurrent();

    private:
        unsigned _buffer;
        BufferMode _mode;
    };
}
