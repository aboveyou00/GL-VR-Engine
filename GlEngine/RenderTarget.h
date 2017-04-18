#pragma once

#include "IAsyncInitializable.h"
#include "RenderStage.h"
#include "RenderTargetViewMode.h"

namespace GlEngine
{
    namespace Impl
    {
        class RenderTargetImpl;
    }

    class ViewPort;
    class Window;
    class ICamera;
    class RenderPipeline;

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

        RenderPipeline* renderPipeline();
        void SetRenderPipeline(RenderPipeline* pipeline);

        virtual ViewPort* viewPort(RenderStage* stage);
        virtual void SetViewPort(RenderStage* stage, ViewPort* viewPort);

        void SetCurrent();

        virtual bool GetShouldRender();

        virtual void Render();
        virtual void Render(RenderPipeline *pipeline);

        virtual void Prepare();
        virtual void PrePush();
        virtual void Push(RenderStage* stage, ICamera* camera);
        virtual void Pop(RenderStage* stage, ICamera* camera);
        virtual void PostPop();

        virtual void Flip();

        void AddToGraphicsLoop();

        inline Impl::RenderTargetImpl &GetImpl()
        {
            return *pimpl;
        }

    protected:
        Impl::RenderTargetImpl *pimpl;
    };
}
