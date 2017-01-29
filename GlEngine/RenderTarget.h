#pragma once

#include "IGraphicsComponent.h"
#include "Camera.h"
#include "RenderTargetLayer.h"

namespace GlEngine
{
    namespace Impl
    {
        class RenderTargetImpl;
    }

    class ViewPort;
    class Window;

    class ENGINE_SHARED RenderTarget : public IGraphicsComponent
    {
    public:
        RenderTarget(Impl::RenderTargetImpl *impl);
        ~RenderTarget();

        virtual bool Initialize();
        virtual void Shutdown();
        virtual bool InitializeGraphics();
        virtual void ShutdownGraphics();

        virtual const char *name();
        void SetViewPort(RenderTargetLayer layer, ViewPort *viewPort);
        ViewPort *viewPort(RenderTargetLayer layer);

        void SetCurrent();

        virtual bool GetShouldRender();

        virtual void Prepare();
        virtual void PrePush();
        virtual void Push(RenderTargetLayer layer);
        virtual void Pop(RenderTargetLayer layer);

        virtual void Flip();

        virtual operator bool() override;

        inline Impl::RenderTargetImpl &GetImpl()
        {
            return *pimpl;
        }

    protected:
        Impl::RenderTargetImpl *pimpl;
    };
}
