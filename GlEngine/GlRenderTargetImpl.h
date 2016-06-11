#pragma once

#include "IComponent.h"
#include "OpenGl.h"
#include "GraphicsContext.h"

namespace GlEngine
{
    class Window;

    namespace Impl
    {
        class GlRenderTargetImpl : public IComponent
        {
        public:
            GlRenderTargetImpl(Window *window);
            ~GlRenderTargetImpl();

            bool Initialize();
            void Shutdown();

			void MakeCurrentTarget();
			void SetGraphicsContext(GraphicsContext * graphicsContext);

			void Render();
			void Flip();

			int depthBufferBits = 24;
			int stencilBufferBits = 8;
			int auxFrameBufferCount = 0;
			int frameBufferColorBits = 32;
			int frameBufferType = PFD_TYPE_RGBA;

			int pixelFormatAdditionalFlags = 0;

        private:
            Window *_window;
			HGLRC contextHandle;

			bool CreateContext();
			bool LoadGlewExtensions();
        };
    }
}
