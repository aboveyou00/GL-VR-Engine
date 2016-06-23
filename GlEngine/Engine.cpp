#include "stdafx.h"
#include "Engine.h"
#include "GlController.h"
#include "WindowManager.h"

#include "ConsoleLogger.h"

namespace GlEngine
{
    void createDefaultServices(ServiceProvider &serviceProvider);

    Engine::Engine()
    {
    }
    Engine::~Engine()
    {
    }

    Engine Engine::_instance;

    bool Engine::Initialize()
    {
        auto &serviceProvider = GetServiceProvider();
        createDefaultServices(GetServiceProvider());
        auto &logger = *serviceProvider.GetService<ILogger>();

        logger.Log(LogType::Info, "Beginning GlEngine initialization.");
        if (!GetWindowManager().Initialize())
        {
            logger.Log(LogType::FatalError, "GlEngine WindowManager failed to initialize, aborting!");
            return false;
        }
        if (!GetGlController().Initialize())
        {
            logger.Log(LogType::FatalError, "GlEngine GlController failed to initialize, aborting!");
            GetWindowManager().Shutdown();
            return false;
        }
        logger.Log(LogType::Info, "GlEngine WindowManager initialization was successful.");
        return true;
    }
    void Engine::Shutdown()
    {
        auto &serviceProvider = GetServiceProvider();
        auto &logger = *serviceProvider.GetService<ILogger>();

        logger.Log(LogType::Info, "~Shutting down GlEngine");

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
    
    rt_mutex &Engine::GetMutex()
    {
        return GetWindowManager().GetMutex();
    }

    void Engine::MessageLoop()
    {
        MSG msg = { };
        for (;; std::this_thread::sleep_for(1ms))
        {
            ScopedLock _lock(GetMutex());
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT) return;
            }
        }
    }

    void createDefaultServices(ServiceProvider &serviceProvider)
    {
        auto logger = serviceProvider.GetService<ILogger>();
        if (logger == nullptr) serviceProvider.RegisterService<ILogger>(logger = new ConsoleLogger());
    }
}
