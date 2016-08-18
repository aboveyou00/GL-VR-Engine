#pragma once

#include "IComponent.h"
#include "OpenGl.h"
#include "ViewPort.h"
#include "RenderTargetLayer.h"

namespace GlEngine
{
    class Window;

    namespace Impl
    {
        class RenderTargetImpl : public IComponent
        {
        public:
			RenderTargetImpl();
            ~RenderTargetImpl();

            virtual bool Initialize();
            void Shutdown();
            const char *name() override;
			virtual void MakeCurrentTarget();

            inline bool GetShouldRender()
            {
                return shouldRender;
            }

			virtual void Prepare();
			virtual void PrePush();
			virtual void Push(RenderTargetLayer layer);
			virtual void Pop(RenderTargetLayer layer);

			virtual void Flip();
			virtual void SetViewPort(RenderTargetLayer layer, ViewPort * viewPort);

			static const int layerCount = (int)std::numeric_limits<RenderTargetLayer>::max() - (int)std::numeric_limits<RenderTargetLayer>::min() + 1;
			ViewPort* viewPorts[layerCount];
			
        private:
            bool shouldRender;
        };
    }
}
