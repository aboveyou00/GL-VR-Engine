#pragma once

namespace GlEngine
{
    class ENGINE_SHARED IAsyncInitializable
    {
    public:
        virtual bool InitializeAsync() = 0;
        virtual void ShutdownAsync() = 0;
        virtual bool InitializeGraphics() = 0;
        virtual void ShutdownGraphics() = 0;

        virtual std::string name() = 0;

        virtual bool needsGraphics();
        virtual bool isReady() = 0;
    };
}
