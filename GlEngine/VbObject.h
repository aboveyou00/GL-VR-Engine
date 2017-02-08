#pragma once

#include "IGraphicsComponent.h"
#include "BufferMode.h"

namespace GlEngine
{
    struct ENGINE_SHARED VbObject : IGraphicsComponent
    {
    public:
        VbObject();
        VbObject(unsigned buff, BufferMode mode);
        ~VbObject();

        bool Initialize();
        void Shutdown();
        bool InitializeGraphics();
        void ShutdownGraphics();

        void MakeCurrent();

        virtual operator bool() override;
        virtual std::string name() override;

    private:
        unsigned _buffer;
        BufferMode _mode;
    };
}
