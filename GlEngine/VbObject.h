#pragma once

#include "IAsyncInitializable.h"
#include "BufferMode.h"

namespace GlEngine
{
    struct ENGINE_SHARED VbObject : IAsyncInitializable
    {
    public:
        VbObject();
        VbObject(unsigned buff, BufferMode mode);
        ~VbObject();

        bool InitializeAsync();
        void ShutdownAsync();
        bool InitializeGraphics();
        void ShutdownGraphics();

        void MakeCurrent();

        bool isReady();

        virtual std::string name() override;

    private:
        unsigned _buffer;
        BufferMode _mode;
    };
}
