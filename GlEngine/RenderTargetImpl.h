#pragma once

#include "IInitializable.h"
#include "ViewPort.h"
#include "RenderTargetViewMode.h"
#include "RenderStage.h"

namespace GlEngine
{
    class ICamera;
    class RenderPipeline;

    namespace Impl
    {
        class RenderTargetImpl : public IAsyncInitializable
        {
        public:
            RenderTargetImpl(RenderPipeline* pipeline = nullptr);
            ~RenderTargetImpl();

            virtual bool InitializeAsync() override;
            virtual void ShutdownAsync() override;
            virtual bool InitializeGraphics() override;
            virtual void ShutdownGraphics() override;

            virtual std::string name() override;

            virtual void MakeCurrentTarget();

            inline bool GetShouldRender()
            {
                return shouldRender;
            }

            virtual void Prepare();
            virtual void PrePush();
            virtual void Push(RenderStage* stage, ICamera* camera);
            virtual void Pop(RenderStage* stage, ICamera* camera);
            virtual void PostPop();

            virtual void Flip();

            RenderPipeline* renderPipeline();
            void SetRenderPipeline(RenderPipeline* pipeline);

            virtual ViewPort* viewPort(RenderStage* stage);
            virtual void SetViewPort(RenderStage* stage, ViewPort* viewPort);

        protected:
            std::map<RenderStage*, ViewPort*> viewPorts;

        private:
            bool shouldRender;
            RenderPipeline* _renderPipeline;
        };
    }
}
