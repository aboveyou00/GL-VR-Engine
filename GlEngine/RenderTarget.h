#pragma once

#include "IAsyncInitializable.h"
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
    class CameraComponent;

    class ENGINE_SHARED RenderTarget : public IAsyncInitializable
    {
    public:
        RenderTarget(Impl::RenderTargetImpl *impl);
        ~RenderTarget();

        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual std::string name();

        virtual bool isReady() override;

        CameraComponent *camera();
        void SetCamera(CameraComponent *camera);

        void SetViewPort(RenderTargetLayer layer, ViewPort *viewPort);
        ViewPort *viewPort(RenderTargetLayer layer);

        void SetCurrent();

        virtual bool GetShouldRender();

        virtual void Render();

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

        void AddToGraphicsLoop();

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
