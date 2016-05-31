#include "stdafx.h"
#include "Engine.h"
#include "GlController.h"
#include "WindowManager.h"

namespace GlEngine
{
    Engine::Engine()
    {
    }
    Engine::~Engine()
    {
    }

    Engine Engine::_instance;

    bool Engine::Initialize()
    {
        if (!GetWindowManager().Initialize()) return false;
        if (!GetGlController().Initialize())
        {
            GetWindowManager().Shutdown();
            return false;
        }
        return true;
    }
    void Engine::Shutdown()
    {
        GetGlController().Shutdown();
        GetWindowManager().Shutdown();
    }

    WindowManager &Engine::GetWindowManager()
    {
        return WindowManager::GetInstance();
    }
    GlController &Engine::GetGlController()
    {
        return GlController::GetInstance();
    }

    void Engine::MessageLoop()
    {
        MSG msg = { };
        for (;;)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT) break;
                continue;
            }
            std::this_thread::sleep_for(1ms);
        }
    }
    void Engine::RenderFrame()
    {

    }
}
