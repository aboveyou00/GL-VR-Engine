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

			bool alive = true;

			void MakeCurrentTarget();
			
			Camera * camera = nullptr;

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

				double left = -1, right = 1, top = 1, bottom = -1, nearVal = 0, farVal = 100;
				void ApplyProjection();
				void Apply();

				void Push();
				void Pop();
			} viewPort;

        private:
            Window *_window;
			HGLRC contextHandle;

			bool CreateContext();
			bool LoadGlewExtensions();
        };
    }
}
