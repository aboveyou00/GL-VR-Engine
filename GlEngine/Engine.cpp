#include "stdafx.h"
#include "Engine.h"
#include "GraphicsController.h"
#include "AudioController.h"
#include "WindowManager.h"

#include "ConsoleLogger.h"
#include "ResourceLoader.h"

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
        createDefaultServices(serviceProvider);
        auto &logger = *serviceProvider.GetService<ILogger>();
        auto &resources = *serviceProvider.GetService<ResourceLoader>();

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
        //if (!GetAudioController().Initialize())
        //{
        //    logger.Log(LogType::FatalError, "GlEngine AlController failed to initialize, aborting!");
        //    GetGlController().Shutdown();
        //    GetWindowManager().Shutdown();
        //    return false;
        //}
        if (!resources.Initialize())
        {
            logger.Log(LogType::FatalError, "GlEngine ResourceLoader failed to initialize, aborting!");
            GetAudioController().Shutdown();
            GetGlController().Shutdown();
            GetWindowManager().Shutdown();
            return false;
        }
        return true;
    }
    void Engine::Shutdown()
    {
        auto &serviceProvider = GetServiceProvider();
        auto &logger = *serviceProvider.GetService<ILogger>();

        logger.Log(LogType::Info, "~Shutting down GlEngine");

        auto &resources = *serviceProvider.GetService<ResourceLoader>();
        resources.Shutdown();
        //GetAudioController().Shutdown();
        GetGlController().Shutdown();
        GetWindowManager().Shutdown();
    }

    WindowManager &Engine::GetWindowManager()
    {
        return WindowManager::GetInstance();
    }
    GraphicsController &Engine::GetGlController()
    {
        return GraphicsController::GetInstance();
    }
    AudioController &Engine::GetAudioController()
    {
        return AudioController::GetInstance();
    }
    
    rt_mutex &Engine::GetMutex()
    {
        return GetWindowManager().GetMutex();
    }

    const char *Engine::name()
    {
        return "Engine";
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
            //GetAudioController().Tick(0); //We don't need a delta here, YSE worries about its own timing
        }
    }

    void createDefaultServices(ServiceProvider &serviceProvider)
    {
        auto logger = serviceProvider.GetService<ILogger>();
        if (logger == nullptr) serviceProvider.RegisterService<ILogger>(logger = new ConsoleLogger());

        serviceProvider.RegisterService(new ResourceLoader());
    }
}
