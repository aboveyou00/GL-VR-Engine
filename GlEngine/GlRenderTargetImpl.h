#pragma once

#include "IComponent.h"
#include "OpenGl.h"
#include "GraphicsContext.h"
#include "Camera.h"

namespace GlEngine
{
    class Window;

    namespace Impl
    {
        class ENGINE_SHARED GlRenderTargetImpl : public IComponent
        {
        public:
			GlRenderTargetImpl(Window * window);
            ~GlRenderTargetImpl();

            bool Initialize();
            void Shutdown();

            const char *name() override;

			bool alive = true;

			void MakeCurrentTarget();
			
			Camera * camera = nullptr;

            inline bool GetShouldRender()
            {
                return shouldRender;
            }

            void Prepare();
			void Push();
			void Pop();

			void Flip();

			int depthBufferBits = 24;
			int stencilBufferBits = 8;
			int auxFrameBufferCount = 0;
			int frameBufferColorBits = 32;
			int frameBufferType = PFD_TYPE_RGBA;

			int pixelFormatAdditionalFlags = 0;

			class ViewPort
            {
			public:
				Camera relativeCamera;

				void ApplyProjection();
				void Apply();

				void Push();
				void Pop();

				void SetSize(int width, int height);
				void SetWidth(int width);
				void SetHeight(int height);
				int GetWidth();
				int GetHeight();
			
			private:
				int width, height;
			
			} viewPort;

        private:
            Window *_window;
			HDC deviceContext;
			HGLRC contextHandle;
            unsigned lastWidth, lastHeight;
            bool shouldRender;

			bool CreateContext();
			bool LoadGlewExtensions();
        };
    }
}
