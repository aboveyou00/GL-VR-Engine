#include "stdafx.h"
#include "GlRenderTargetImpl.h"
#include "Window.h"

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

            return true;
        }

        void GlRenderTargetImpl::Shutdown()
        {
			wglMakeCurrent(_window->GetDeviceContext(), nullptr);
			wglDeleteContext(contextHandle);
        }

		void GlRenderTargetImpl::MakeCurrentTarget()
		{
			wglMakeCurrent(_window->GetDeviceContext(), contextHandle);
		}

		void GlRenderTargetImpl::SetGraphicsContext(GraphicsContext *graphicsContext)
		{
            graphicsContext;
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

		void GlRenderTargetImpl::Flip()
		{
			SwapBuffers(_window->GetDeviceContext());
		}
    }
}
