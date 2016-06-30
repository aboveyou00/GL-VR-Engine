#include "stdafx.h"
#include "GlRenderTargetImpl.h"

#include "Window.h"
#include <chrono>

namespace GlEngine
{
    namespace Impl
    {
		GlRenderTargetImpl::GlRenderTargetImpl(Window *window)
			: _window(window), deviceContext(_window->GetDeviceContext())
        {
		}
        GlRenderTargetImpl::~GlRenderTargetImpl()
        {
        }

        bool GlRenderTargetImpl::Initialize()
        {
			if (!CreateContext()) return false;
			MakeCurrentTarget();
			if (!LoadGlewExtensions()) return false;
            return true;
        }

        void GlRenderTargetImpl::Shutdown()
        {
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(contextHandle);
        }

		void GlRenderTargetImpl::MakeCurrentTarget()
		{
			wglMakeCurrent(deviceContext, contextHandle);
		}

		bool GlRenderTargetImpl::CreateContext()
		{
			/* Pixel format options we would like (NOT guaranteed) to have */
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

			glewExperimental = TRUE;
			GLenum err = glewInit();
            if (err != GLEW_OK)
            {
                std::cout << "GLEW error: " << glewGetErrorString(err) << std::endl;
                return false;
            }
			
			/* TODO: Load any glew extensions
			glewGetExtension();
			*/	

			return true;
		}

		void GlRenderTargetImpl::Push()
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glDepthFunc(GL_LEQUAL);

            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			viewPort.Push();
		}

		void GlRenderTargetImpl::Pop()
		{
			viewPort.Pop();
		}

		void GlRenderTargetImpl::Flip()
		{
			SwapBuffers(deviceContext);
		}

		void GlRenderTargetImpl::ViewPort::ApplyProjection()
		{
			glLoadIdentity();
			//glFrustum()
			glOrtho(left, right, bottom, top, nearVal, farVal);
		}

		void GlRenderTargetImpl::ViewPort::Apply()
		{
			//relativeCamera.Apply();
			ApplyProjection();
		}

		void GlRenderTargetImpl::ViewPort::Push()
		{
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			Apply();
		}

		void GlRenderTargetImpl::ViewPort::Pop()
		{
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
		}
    }
}
