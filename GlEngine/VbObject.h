#pragma once

#include "IComponent.h"
#include "BufferMode.h"

namespace GlEngine
{
    struct ENGINE_SHARED VbObject : IComponent
    {
    public:
        VbObject();
        VbObject(unsigned vao, unsigned buff, BufferMode mode);
        ~VbObject();

        bool Initialize();
        void Shutdown();

        void MakeCurrent();

        inline operator bool()
        {
            return _vao != 0 && _buffer != 0;
        }

    private:
        unsigned _vao;
        unsigned _buffer;
        BufferMode _mode;
    };
}
