#include "stdafx.h"
#include "WindowRenderTargetImpl.h"
#include "Window.h"

namespace GlEngine
{
	namespace Impl
	{
		WindowRenderTargetImpl::WindowRenderTargetImpl(Window *window)
			: _window(window), deviceContext(_window->GetDeviceContext())
        {
		}
		WindowRenderTargetImpl::~WindowRenderTargetImpl()
        {
        }

        bool WindowRenderTargetImpl::Initialize()
        {
			if (!CreateContext()) return false;
			MakeCurrentTarget();
			if (!LoadGlewExtensions()) return false;
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
			//assert(false);
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

		bool WindowRenderTargetImpl::LoadGlewExtensions()
		{
			glewExperimental = TRUE;
			GLenum err = glewInit();
            if (err != GLEW_OK)
            {
                std::cout << "GLEW error: " << glewGetErrorString(err) << std::endl;
                return false;
            }
			
			//TODO: Load any glew extensions
			//glewGetExtension();

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
					viewPort->SetSize(this->lastWidth, this->lastHeight);
					shouldRender = true;
                }
            }
        }
        void WindowRenderTargetImpl::Push()
		{
			glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable(GL_TEXTURE_2D);
			glDepthFunc(GL_LEQUAL);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// TODO: this might be more efficient then :
			// float currentFrameBuffer; glGet(GL_FRAME_BUFFER_BINDING, &currentFrameBuffer); 
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, this->lastWidth, this->lastHeight);

			viewPort->Push();
		}
		void WindowRenderTargetImpl::Pop()
		{
			viewPort->Pop();
		}

		void WindowRenderTargetImpl::Flip()
		{
			SwapBuffers(deviceContext);
		}
	}
}