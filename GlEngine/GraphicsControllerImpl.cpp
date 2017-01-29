#include "stdafx.h"
#include "GraphicsControllerImpl.h"
#include "Matrix.h"
#include "OpenGl.h"
#include "WindowsUtils.h"
#include "LogUtils.h"
#include "Engine.h"
#include "WindowManager.h"
#include "ResourceLoader.h"

namespace GlEngine
{
    namespace Impl
    {
        GraphicsControllerImpl::GraphicsControllerImpl()
            : _loop(
                [&] { return this->InitializeGraphicsThread(); },
                [&](float delta) { this->Tick(delta); },
                [&] { this->ShutdownGraphicsThread(); }
              )
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
            _loop.RunLoop();
            return true;
        }
        void GraphicsControllerImpl::Shutdown()
        {
            _loop.StopLoop(false);
            Engine::GetInstance().GetWindowManager().Destroy(dummyWindow);
        }

        void GraphicsControllerImpl::AddGraphicsContext(GraphicsContext *graphicsContext)
        {
            assert(graphicsContextCount <= MAX_GRAPHICS_CONTEXTS);
            graphicsContexts[graphicsContextCount++] = graphicsContext;
            auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
            resources->QueueInitialize(graphicsContext);
        }

        rt_mutex &GraphicsControllerImpl::GetMutex()
        {
            return _lock;
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

        bool GraphicsControllerImpl::InitializeGraphicsThread()
        {
            this_thread_name() = "graphics";
            this_thread_type() = ThreadType::Graphics;

            auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            logger->Log(GlEngine::LogType::Info, "Beginning OpenGL graphics thread");

            return true;
        }
        void GraphicsControllerImpl::Tick(float delta)
        {
            auto &resources = *Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
            resources.TickGraphics();

            for (size_t q = 0; q < graphicsContextCount; q++)
                graphicsContexts[q]->Tick(delta);
        }
        void GraphicsControllerImpl::ShutdownGraphicsThread()
        {
            auto &resources = *Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
            resources.ShutdownGraphics();

            auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            logger->Log(GlEngine::LogType::Info, "Terminating OpenGL graphics thread");
        }
    }
}
