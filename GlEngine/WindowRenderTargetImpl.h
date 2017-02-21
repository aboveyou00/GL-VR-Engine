#pragma once

#include "RenderTargetImpl.h"

namespace GlEngine::Impl
{
    class WindowRenderTargetImpl : public RenderTargetImpl
    {
    public:
        WindowRenderTargetImpl(Window *window);
        ~WindowRenderTargetImpl();

        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual std::string name() override;

        bool alive = true;

        virtual void MakeCurrentTarget() override;

        virtual void Prepare() override;
        virtual void PrePush() override;

        virtual void Flip() override;

        int depthBufferBits = 24;
        int stencilBufferBits = 8;
        int auxFrameBufferCount = 0;
        int frameBufferColorBits = 32;
        int frameBufferType = PFD_TYPE_RGBA;

        int pixelFormatAdditionalFlags = 0;

        virtual bool isReady() override;

    private:
        Window *_window;
        HDC deviceContext;
        HGLRC contextHandle;
        unsigned lastWidth, lastHeight;
        bool shouldRender, initialized;

        bool CreateContext();
    };
}
