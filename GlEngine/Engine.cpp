#include "stdafx.h"
#include "Engine.h"
#include "GlController.h"
#include "AlController.h"
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
        if (!GetAlController().Initialize())
        {
            GetGlController().Shutdown();
            GetWindowManager().Shutdown();
            return false;
        }
        return true;
    }
    void Engine::Shutdown()
    {
        GetAlController().Shutdown();
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
    AlController &Engine::GetAlController()
    {
        return AlController::GetInstance();
    }

    void Engine::MessageLoop()
    {
        MSG msg = { };
        for (;; std::this_thread::sleep_for(1ms))
        {
            ScopedLock _lock(GetWindowManager().GetMutex());
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT) return;
            }
        }
    }
}
