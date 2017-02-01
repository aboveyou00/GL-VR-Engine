#pragma once

#include "IGraphicsComponent.h"
#include "OpenGl.h"
#include "ViewPort.h"
#include "RenderTargetLayer.h"
#include "RenderTargetViewMode.h"

namespace GlEngine
{
    namespace Impl
    {
        class RenderTargetImpl : public IGraphicsComponent
        {
        public:
            RenderTargetImpl();
            ~RenderTargetImpl();

            virtual bool Initialize() override;
            virtual void Shutdown() override;
            virtual bool InitializeGraphics() override;
            virtual void ShutdownGraphics() override;

            const char *name() override;
            
            virtual void MakeCurrentTarget();

            inline bool GetShouldRender()
            {
                return shouldRender;
            }

            virtual void Prepare();
            virtual void PrePush();
            virtual void Push(RenderTargetLayer layer, RenderTargetViewMode viewMode, Matrix<4, 4> viewMatrix);
            virtual void Pop(RenderTargetLayer layer);
            virtual void PostPop();

            virtual void Flip();

            virtual void SetViewPort(RenderTargetLayer layer, ViewPort *viewPort);
            ViewPort *viewPort(RenderTargetLayer layer);

            static const int layerCount = (int)std::numeric_limits<RenderTargetLayer>::max() - (int)std::numeric_limits<RenderTargetLayer>::min() + 1;
            ViewPort* viewPorts[layerCount];
            
        private:
            bool shouldRender;
        };
    }
}
