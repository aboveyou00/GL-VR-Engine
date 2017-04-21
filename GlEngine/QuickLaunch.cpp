#include "stdafx.h"
#include "QuickLaunch.h"
#include "QuickLaunchLoop.h"
#include "FrameStack.h"

#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsController.h"
#include "WindowRenderTarget.h"

#include "PerspectiveViewPort.h"
#include "OrthoViewPort.h"

#include "FileLogger.h"
#include "FileConfigProvider.h"

namespace GlEngine
{
    QuickLaunch::QuickLaunch(std::string name, std::string logName, std::string configName, unsigned frameRate)
        : _name(name), _logName(logName), _configName(configName), _loop(new QuickLaunchLoop(frameRate)), _gfxAdapter(nullptr)
    {
    }
    QuickLaunch::~QuickLaunch()
    {
        Shutdown();
    }

    void QuickLaunch::SetInitialFrame(Frame *frame)
    {
        _loop->SetInitialFrame(frame);
    }

    bool QuickLaunch::Initialize()
    {
        logger = registerLogger();
        if (logger == nullptr) return false;

        logger->Log(GlEngine::LogType::InfoC, "Welcome to %s! Beginning initialization...", _name.c_str());

        config = registerConfig();
        if (config == nullptr) return false;

        if (!createWindow())
        {
            logger->Log(GlEngine::LogType::FatalErrorC, "Could not create window. Aborting %s initialization...", _name.c_str());
            Shutdown();
            return false;
        }
        if (!_loop->Initialize())
        {
            logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize %s loop. Aborting...", _name.c_str());
            Shutdown();
            return false;
        }

        logger->Log(GlEngine::LogType::InfoC, "%s initialization successful. Beginning game.", _name.c_str());
        return true;
    }
    void QuickLaunch::Shutdown()
    {
        logger->Log(GlEngine::LogType::Info, "~Shutting down %s...", _name.c_str());

        _loop->Shutdown();
        destroyWindow();
    }

    std::string QuickLaunch::name()
    {
        return "QuickLaunch";
    }

    void QuickLaunch::MessageLoop()
    {
        logger->Log(GlEngine::LogType::Info, "Beginning WndProc on thread [%s]...", this_thread_name().c_str());

        auto &engine = GlEngine::Engine::GetInstance();
        engine.MessageLoop();

        logger->Log(GlEngine::LogType::Info, "~Terminating WndProc...");
    }

    QuickLaunchLoop &QuickLaunch::GetLoop()
    {
        return *_loop;
    }
    GlEngine::Window &QuickLaunch::GetWindow()
    {
        return *_window;
    }

    bool QuickLaunch::createWindow()
    {
        auto &engine = GlEngine::Engine::GetInstance();
        if (!engine.Initialize()) return false;

        _window = engine.GetWindowManager().Create();
        if (_window == nullptr)
        {
            engine.Shutdown();
            return false;
        }

        if (config->GetValueWithDefault("Fullscreen", true)) _window->SetFullscreen(true);
        _window->SetCenterCursor(true);

        auto windowRenderTarget = new GlEngine::WindowRenderTarget(_window);
        windowRenderTarget->SetRenderPipeline(_loop->frames());
        windowRenderTarget->SetViewPort(GlEngine::renderStage_opaque, new GlEngine::PerspectiveViewPort());
        windowRenderTarget->SetViewPort(GlEngine::renderStage_translucent, new GlEngine::PerspectiveViewPort());
        windowRenderTarget->SetViewPort(GlEngine::renderStage_2d, new GlEngine::OrthoViewPort());
        windowRenderTarget->AddToGraphicsLoop();

        _window->Show();

        return true;
    }

    void QuickLaunch::destroyWindow()
    {
        _window->Hide();

        auto &engine = GlEngine::Engine::GetInstance();
        engine.Shutdown();
    }

    GlEngine::ILogger *QuickLaunch::registerLogger()
    {
        auto f_logger = new GlEngine::FileLogger("", _logName.c_str());
        if (!f_logger->Initialize())
        {
            f_logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize file logger. Aborting");
            return nullptr;
        }

        auto &serviceProvider = GlEngine::Engine::GetInstance().GetServiceProvider();
        serviceProvider.RegisterService<GlEngine::ILogger>(f_logger);
        return f_logger;
    }

    GlEngine::IConfigProvider *QuickLaunch::registerConfig()
    {
        auto f_config = new GlEngine::FileConfigProvider("", _configName.c_str());
        if (!f_config->Initialize())
        {
            logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize file config provider. Aborting");
            return nullptr;
        }

        auto &serviceProvider = GlEngine::Engine::GetInstance().GetServiceProvider();
        serviceProvider.RegisterService<GlEngine::IConfigProvider>(f_config);
        return f_config;
    }
}
