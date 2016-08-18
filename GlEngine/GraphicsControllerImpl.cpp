#include "stdafx.h"
#include "GraphicsControllerImpl.h"
#include "Matrix.h"
#include "OpenGl.h"
#include "WindowsUtils.h"
#include "LogUtils.h"
#include "Engine.h"
#include "WindowManager.h"

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
			wglMakeCurrent(nullptr, nullptr);
            return true;
        }
        void GraphicsControllerImpl::Shutdown()
        {
			Engine::GetInstance().GetWindowManager().Destroy(dummyWindow);
        }

		void GraphicsControllerImpl::MakeDefaultContext()
		{
			dummyWindow = Engine::GetInstance().GetWindowManager().Create();
			
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				(DWORD)(PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER),    //Flags
				PFD_TYPE_RGBA,          //The kind of framebuffer. RGBA or palette.
				32,    //Colordepth of the framebuffer.
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24,         //Number of bits for the depthbuffer
				8,       //Number of bits for the stencilbuffer
				0,     //Number of Aux buffers in the framebuffer
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};

			HDC dc = dummyWindow->GetDeviceContext();
			int format = ChoosePixelFormat(dc, &pfd);
			SetPixelFormat(dc, format, &pfd);

			HGLRC ch = wglCreateContext(dc);
			if (ch == nullptr)
				Util::Log(LogType::ErrorC, "wglCreateContext failed: " + Util::GetLastErrorAsString());
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
