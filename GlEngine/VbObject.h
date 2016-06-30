#pragma once

#include "IComponent.h"
#include "BufferMode.h"

namespace GlEngine
{
    struct ENGINE_SHARED VbObject : IComponent
    {
    public:
        VbObject();
        VbObject(unsigned vao, unsigned buff);
        VbObject(unsigned buff, BufferMode mode);
        VbObject(unsigned vao, unsigned buff, BufferMode mode);
        ~VbObject();

        bool Initialize();
        void Shutdown();

        void MakeCurrent();

        operator bool();

    private:
        unsigned _vao;
        unsigned _buffer;
        BufferMode _mode;
    };
}
