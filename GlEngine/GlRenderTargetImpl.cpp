#include "stdafx.h"
#include "GlRenderTargetImpl.h"
#include "MatrixStack.h"
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

        const char *GlRenderTargetImpl::name()
        {
            return "GlRenderTargetImpl";
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

        void GlRenderTargetImpl::Prepare()
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
					viewPort.SetSize(this->lastWidth, this->lastHeight);
					shouldRender = true;
                }
            }
        }
        void GlRenderTargetImpl::Push()
		{
			glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable(GL_TEXTURE_2D);
			glDepthFunc(GL_LEQUAL);

            static float theta = .5f;
            theta += .01f;
            glUniform3f(2, sin(theta), -.5f, cos(theta));
            glUniform3f(3, .4f, .6f, 1.f);
            glUniform3f(4, .1f, .1f, .1f);

            //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
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

		void GlRenderTargetImpl::ViewPort::Push()
		{
            //relativeCamera.Apply();

            float viewWidth, viewHeight;
            if (width > height)
            {
                viewHeight = 1.0;
                viewWidth = (float)width / height;
            }
            else
            {
                viewWidth = 1.0;
                viewHeight = (float)height / width;
            }

            float nearVal = 1.f;
            float farVal = 100.f;

            MatrixStack::Projection.push(Mat3T<float>::Frustum(-viewWidth / 2, viewWidth / 2, -viewHeight / 2, viewHeight / 2, nearVal, farVal));
            MatrixStack::Projection.tell_gl();
            //glOrtho(left, right, bottom, top, nearVal, farVal);
            //ProjectionMatrixStack.push(Mat3T<float>::Ortho(left, right, bottom, top, nearVal, farVal));
		}

		void GlRenderTargetImpl::ViewPort::Pop()
		{
            MatrixStack::Projection.pop();
            MatrixStack::Projection.tell_gl();
		}

		void GlRenderTargetImpl::ViewPort::SetSize(int width, int height)
		{
			this->width = width;
			this->height = height;
		}
		void GlRenderTargetImpl::ViewPort::SetWidth(int width)
		{
			this->width = width;
		}
		void GlRenderTargetImpl::ViewPort::SetHeight(int height)
		{
			this->height = height;
		}

		int GlRenderTargetImpl::ViewPort::GetWidth()
		{
			return width;
		}

		int GlRenderTargetImpl::ViewPort::GetHeight()
		{
			return height;
		}
    }
}
