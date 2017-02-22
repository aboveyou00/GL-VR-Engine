#include "stdafx.h"
#include "WindowRenderTargetImpl.h"
#include "Window.h"
#include "MatrixStack.h"

namespace GlEngine::Impl
{
    WindowRenderTargetImpl::WindowRenderTargetImpl(Window *window)
        : RenderTargetImpl(),
          _window(window), deviceContext(_window->GetDeviceContext()),
          lastWidth(0), lastHeight(0),
          initialized(false)
    {
    }
    WindowRenderTargetImpl::~WindowRenderTargetImpl()
    {
    }

    bool WindowRenderTargetImpl::InitializeAsync()
    {
        if (!RenderTargetImpl::InitializeAsync()) return false;
        if (!CreateContext()) return false;
        return initialized = true;
    }
    void WindowRenderTargetImpl::ShutdownAsync()
    {
        RenderTargetImpl::ShutdownAsync();
        wglDeleteContext(contextHandle);
    }
    bool WindowRenderTargetImpl::InitializeGraphics()
    {
        if (!RenderTargetImpl::InitializeGraphics()) return false;
        MakeCurrentTarget();
        return true;
    }
    void WindowRenderTargetImpl::ShutdownGraphics()
    {
        RenderTargetImpl::ShutdownGraphics();
        //wglMakeCurrent(nullptr, nullptr);
    }

    std::string WindowRenderTargetImpl::name()
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

    bool WindowRenderTargetImpl::isReady()
    {
        return initialized;
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
                checkForGlError();
                for (int i = 0; i < layerCount; i++)
                    if (viewPorts[i] != nullptr)
                        viewPorts[i]->SetSize(this->lastWidth, this->lastHeight);
                shouldRender = true;
            }
        }
    }
    void WindowRenderTargetImpl::PrePush()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        checkForGlError();
        glViewport(0, 0, this->lastWidth, this->lastHeight);
        checkForGlError();

        RenderTargetImpl::PrePush();
    }

    void WindowRenderTargetImpl::Flip()
    {
        SwapBuffers(deviceContext);
    }
}
