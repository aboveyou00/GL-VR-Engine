#include "stdafx.h"
#include "GraphicsControllerImpl.h"
#include "Matrix.h"
#include "LogUtils.h"
#include "Engine.h"
#include "WindowManager.h"
#include "ResourceLoader.h"

#include "Engine.h"
#include "GraphicsAdapter.h"

#include "CameraComponent.h"
#include "Frame.h"
#include "RenderTarget.h"
#include "RenderPipeline.h"

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
            CreateDummyWindow();
            _loop.RunLoop();
            return true;
        }
        void GraphicsControllerImpl::Shutdown()
        {
            _loop.StopLoop(false);
            Engine::GetInstance().GetWindowManager().Destroy(dummyWindow);
        }

        void GraphicsControllerImpl::AddRenderTarget(RenderTarget *target)
        {
            renderTargets.push_back(target);
            auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
            resources->QueueInitialize(target);
        }

        rt_mutex &GraphicsControllerImpl::GetMutex()
        {
            return _lock;
        }

        void GraphicsControllerImpl::CreateDummyWindow()
        {
            dummyWindow = Engine::GetInstance().GetWindowManager().Create();

            PIXELFORMATDESCRIPTOR pfd =
            {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                (DWORD)(PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER), //Flags
                PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
                32, //Colordepth of the framebuffer.
                0, 0, 0, 0, 0, 0,
                0,
                0,
                0,
                0, 0, 0, 0,
                24, //Number of bits for the depthbuffer
                8, //Number of bits for the stencilbuffer
                0, //Number of Aux buffers in the framebuffer
                PFD_MAIN_PLANE,
                0,
                0, 0, 0
            };

            _hdc = dummyWindow->GetDeviceContext();
            int format = ChoosePixelFormat(_hdc, &pfd);
            SetPixelFormat(_hdc, format, &pfd);
        }

        void GraphicsControllerImpl::MakeDefaultContext()
        {
        }

        std::string GraphicsControllerImpl::name()
        {
            return "GlControllerImpl";
        }

        bool GraphicsControllerImpl::InitializeGraphicsThread()
        {
            this_thread_name() = "graphics";
            this_thread_type() = ThreadType::Graphics;

            THIS_ENGINE.graphicsAdapter().MakeDefaultContext(_hdc);

            Util::Log(GlEngine::LogType::Info, "Beginning graphics thread");

            return true;
        }
        void GraphicsControllerImpl::Tick(float delta)
        {
            auto &resources = *Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
            resources.TickGraphics();

            std::vector<RenderTarget*> targets;
            std::vector<Frame*> frames;

            ScopedLock _lock(_lock);

            for (size_t q = 0; q < renderTargets.size(); q++)
            {
                auto target = renderTargets[q];
                if (!target->isReady() || !target->GetShouldRender()) continue;
                targets.push_back(target);
                target->Prepare();

                auto thisPipeline = target->renderPipeline();
                Frame *thisFrame = nullptr;
                if (thisPipeline != nullptr) thisFrame = thisPipeline->frame();
                if (thisFrame != nullptr && std::find(frames.begin(), frames.end(), thisFrame) == frames.end())
                {
                    frames.push_back(thisFrame);
                }
            }
            if (targets.size() == 0) return;

            for (size_t q = 0; q < frames.size(); q++)
            {
                frames[q]->TickGraphics(delta);
            }

            for (size_t q = 0; q < targets.size(); q++)
            {
                targets[q]->Render();
            }

            for (size_t q = 0; q < targets.size(); q++)
            {
                targets[q]->Flip();
            }
        }
        void GraphicsControllerImpl::ShutdownGraphicsThread()
        {
            auto &resources = *Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
            resources.ShutdownGraphics();

            Util::Log(GlEngine::LogType::Info, "Terminating OpenGL graphics thread");
        }
    }
}
