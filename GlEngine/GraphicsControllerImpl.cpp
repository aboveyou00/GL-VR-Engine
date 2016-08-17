#include "stdafx.h"
#include "GraphicsControllerImpl.h"
#include "Matrix.h"
#include "OpenGl.h"

namespace GlEngine
{
    namespace Impl
    {
        GraphicsControllerImpl::GraphicsControllerImpl()
        {
        }
        GraphicsControllerImpl::~GraphicsControllerImpl()
        {
        }

        bool GraphicsControllerImpl::Initialize()
        {
			MakeDefaultContext();
			LoadGlewExtensions();
            return true;
        }
        void GraphicsControllerImpl::Shutdown()
        {
        }

		void GraphicsControllerImpl::MakeDefaultContext()
		{
			HWND device = GetDesktopWindow();
			HDC dc = GetDC(device);
			HGLRC ch = wglCreateContext(dc);
			wglMakeCurrent(dc, ch);
		}

		bool GraphicsControllerImpl::LoadGlewExtensions()
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

        const char *GraphicsControllerImpl::name()
        {
            return "GlControllerImpl";
        }
    }
}
