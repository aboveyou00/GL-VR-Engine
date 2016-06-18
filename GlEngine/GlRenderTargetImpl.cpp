#include "stdafx.h"
#include "GlRenderTargetImpl.h"

#include "Window.h"
#include <chrono>

namespace GlEngine
{
    namespace Impl
    {
        GlRenderTargetImpl::GlRenderTargetImpl(Window *window)
            : _window(window)
        {
        }
        GlRenderTargetImpl::~GlRenderTargetImpl()
        {
        }

        bool GlRenderTargetImpl::Initialize()
        {
			if (!CreateContext()) return false;
			if (!LoadGlewExtensions()) return false;
			MakeCurrentTarget();

			camera.SetEye({ 0, 0, 0 });
			camera.SetUp({ 0, 1, 0 });
			camera.SetCenter({ 0, 0, 1 });

            return true;
        }

        void GlRenderTargetImpl::Shutdown()
        {
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(contextHandle);
        }

		void GlRenderTargetImpl::MakeCurrentTarget()
		{
			wglMakeCurrent(_window->GetDeviceContext(), contextHandle);
		}

		void GlRenderTargetImpl::SetGraphicsContext(GraphicsContext * context)
		{
            graphicsContext = context;
		}

		bool GlRenderTargetImpl::CreateContext()
		{
			/* Pixel format ptions we would like (NOT guaranteed) to have */
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				(DWORD)(PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | pixelFormatAdditionalFlags),    //Flags
				(BYTE)frameBufferType,          //The kind of framebuffer. RGBA or palette.
				(BYTE)frameBufferColorBits,    //Colordepth of the framebuffer.
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				(BYTE)depthBufferBits,         //Number of bits for the depthbuffer
				(BYTE)stencilBufferBits,       //Number of bits for the stencilbuffer
				(BYTE)auxFrameBufferCount,     //Number of Aux buffers in the framebuffer.
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};

			/* Find closest pixel format and device context with it */
			HDC dc = _window->GetDeviceContext();
			int format = ChoosePixelFormat(dc, &pfd);
			SetPixelFormat(dc, format, &pfd);

			/* Create the opengl context */
			contextHandle = wglCreateContext(dc);

			return true;
		}

		bool GlRenderTargetImpl::LoadGlewExtensions()
		{
			// TODO: helpful errors
			
			//glewExperimental = TRUE;
			//GLenum err = glewInit();
			//if (err != GLEW_OK)
			//	return false;
			
			/* TODO: Load any glew extensions
			glewGetExtension();
			*/

			return true;
		}

		void GlRenderTargetImpl::Loop(double fps)
		{
			auto frame_duration = 1000ms / fps;

			while (alive)
			{
				auto start = std::chrono::high_resolution_clock::now();
				Render();
				auto end = std::chrono::high_resolution_clock::now();
				
				auto duration = end - start;
				std::this_thread::sleep_for(frame_duration - duration);
			}
		}

		void GlRenderTargetImpl::Render()
		{
			if (graphicsContext == nullptr)
				return;
			MakeCurrentTarget();
			
			glLoadIdentity();
			camera.ApplyView();
			camera.ApplyProjection();
			
			graphicsContext->Render();
		}

		void GlRenderTargetImpl::Flip()
		{
			SwapBuffers(_window->GetDeviceContext());
		}
    }
}
