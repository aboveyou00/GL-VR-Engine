#pragma once

#include "IComponent.h"
#include "OpenGl.h"
#include "ViewPort.h"

namespace GlEngine
{
    class Window;

    namespace Impl
    {
        class ENGINE_SHARED RenderTargetImpl : public IComponent
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
			virtual void Push();
			virtual void Pop();

			virtual void Flip();
			virtual void SetViewPort(ViewPort * viewPort);

			ViewPort * viewPort;

        private:
            bool shouldRender;
        };
    }
}
