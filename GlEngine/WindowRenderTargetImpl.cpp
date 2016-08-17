#include "stdafx.h"
#include "WindowRenderTargetImpl.h"
#include "Window.h"

namespace GlEngine
{
	namespace Impl
	{
		WindowRenderTargetImpl::WindowRenderTargetImpl(Window *window)
			: _window(window), deviceContext(_window->GetDeviceContext()), lastWidth(0), lastHeight(0)
        {
		}
		WindowRenderTargetImpl::~WindowRenderTargetImpl()
        {
        }

        bool WindowRenderTargetImpl::Initialize()
        {
			if (!CreateContext()) return false;
			MakeCurrentTarget();
			return true;
        }

        void WindowRenderTargetImpl::Shutdown()
        {
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(contextHandle);
        }

        const char *WindowRenderTargetImpl::name()
        {
            return "WindowRenderTargetImpl";
        }

		void WindowRenderTargetImpl::MakeCurrentTarget()
		{
			wglMakeCurrent(deviceContext, contextHandle);
		}

		bool WindowRenderTargetImpl::CreateContext()
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

        void WindowRenderTargetImpl::Prepare()
        {
            if (_window->GetWidth() != this->lastWidth || _window->GetHeight() != this->lastHeight)
            {
                shouldRender = false;
                this->lastWidth = _window->GetWidth();
                this->lastHeight = _window->GetHeight();
            }
            else if (!shouldRender)
            {
                if (_window->GetLastResizeTime() < std::chrono::high_resolution_clock::now() - 50ms)
                {
                    glViewport(0, 0, this->lastWidth, this->lastHeight);
					for (int i = 0; i < layerCount; i++)
						if (viewPorts[i] != nullptr)
							viewPorts[i]->SetSize(this->lastWidth, this->lastHeight);
					shouldRender = true;
                }
            }
        }
        void WindowRenderTargetImpl::Push(RenderTargetLayer layer)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable(GL_TEXTURE_2D);
			glDepthFunc(GL_LEQUAL);

            static float theta = .5f;
            theta += .01f;
            glUniform3f(2, sin(theta), .5f, cos(theta));
            glUniform3f(3, .4f, .6f, 1.f);
            glUniform3f(4, .4f, .4f, .4f);

            //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glViewport(0, 0, this->lastWidth, this->lastHeight);

			RenderTargetImpl::Push(layer);
		}
		void WindowRenderTargetImpl::Pop(RenderTargetLayer layer)
		{
			RenderTargetImpl::Pop(layer);
		}

		void WindowRenderTargetImpl::Flip()
		{
			SwapBuffers(deviceContext);
		}
	}
}