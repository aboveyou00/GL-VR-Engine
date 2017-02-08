#pragma once

#include "IGraphicsComponent.h"
#include "Camera.h"
#include "RenderTargetLayer.h"
#include "RenderTargetViewMode.h"

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

        virtual std::string name();
        void SetViewPort(RenderTargetLayer layer, ViewPort *viewPort);
        ViewPort *viewPort(RenderTargetLayer layer);

        void SetCurrent();

        virtual bool GetShouldRender();

        virtual void Prepare();
        virtual void PrePush();
        virtual void Push(RenderTargetLayer layer);
        virtual void Pop(RenderTargetLayer layer);
        virtual void PostPop();

        virtual void Flip();

        RenderTargetViewMode viewMode();
        void SetViewMode(RenderTargetViewMode mode);

        Matrix<4, 4> viewMatrix();
        void SetViewMatrix(Matrix<4, 4> mat);

        virtual operator bool() override;

        inline Impl::RenderTargetImpl &GetImpl()
        {
            return *pimpl;
        }

    protected:
        Impl::RenderTargetImpl *pimpl;
        RenderTargetViewMode _viewMode;
        Matrix<4, 4> _viewMatrix;
    };
}
