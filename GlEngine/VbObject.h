#pragma once

#include "IGraphicsComponent.h"
#include "BufferMode.h"

namespace GlEngine
{
    struct ENGINE_SHARED VbObject : IGraphicsComponent
    {
    public:
        VbObject();
        VbObject(unsigned vao, unsigned buff);
        VbObject(unsigned buff, BufferMode mode);
        VbObject(unsigned vao, unsigned buff, BufferMode mode);
        ~VbObject();

        bool Initialize();
        void Shutdown();
        bool InitializeGraphics();
        void ShutdownGraphics();

        void MakeCurrent();

        operator bool();
        const char *name() override;

    private:
        unsigned _vao;
        unsigned _buffer;
        BufferMode _mode;
    };
}
