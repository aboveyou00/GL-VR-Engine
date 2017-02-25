#include "stdafx.h"
#include "Sandbox.h"

#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsController.h"
#include "WindowRenderTarget.h"

#include "PerspectiveViewPort.h"
#include "OrthoViewPort.h"

#include "FileLogger.h"
#include "FileConfigProvider.h"

Sandbox::Sandbox()
{
}
Sandbox::~Sandbox()
{
    Shutdown();
}

bool Sandbox::Initialize()
{
    logger = registerLogger();
    if (logger == nullptr) return false;

    logger->Log(GlEngine::LogType::InfoC, "Welcome to our sandbox app! Beginning initialization...");

    config = registerConfig();
    if (config == nullptr) return false;

    if (!createWindow())
    {
        logger->Log(GlEngine::LogType::FatalErrorC, "Could not create window. Aborting...");
        Shutdown();
        return false;
    }
    if (!_loop.Initialize())
    {
        logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize sandbox loop. Aborting...");
        Shutdown();
        return false;
    }

    logger->Log(GlEngine::LogType::InfoC, "Sandbox initialization successful. Beginning game.");
    return true;
}
void Sandbox::Shutdown()
{
    logger->Log(GlEngine::LogType::Info, "~Shutting down sandbox...");

    _loop.Shutdown();
    destroyWindow();
}

std::string Sandbox::name()
{
    return "Sandbox";
}

void Sandbox::MessageLoop()
{
    logger->Log(GlEngine::LogType::Info, "Beginning WndProc on thread [%s]...", this_thread_name().c_str());

    auto &engine = GlEngine::Engine::GetInstance();
    engine.MessageLoop();

    logger->Log(GlEngine::LogType::Info, "~Terminating WndProc...");
}

bool Sandbox::createWindow()
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
    //_window->SetCenterCursor(true);

    auto windowRenderTarget = new GlEngine::WindowRenderTarget(_window);
    windowRenderTarget->SetCamera(this->_loop.frames());
    windowRenderTarget->AddToGraphicsLoop();

    _window->Show();

    return true;
}

void Sandbox::destroyWindow()
{
    _window->Hide();

    auto &engine = GlEngine::Engine::GetInstance();
    engine.Shutdown();
}

GlEngine::ILogger *Sandbox::registerLogger()
{
    auto f_logger = new GlEngine::FileLogger("", "sandbox.log");
    if (!f_logger->Initialize())
    {
        f_logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize file logger. Aborting");
        return nullptr;
    }

    auto &serviceProvider = GlEngine::Engine::GetInstance().GetServiceProvider();
    serviceProvider.RegisterService<GlEngine::ILogger>(f_logger);
    return f_logger;
}

GlEngine::IConfigProvider *Sandbox::registerConfig()
{
    auto f_config = new GlEngine::FileConfigProvider("", "sandbox.config");
    if (!f_config->Initialize())
    {
        logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize file config provider. Aborting");
        return nullptr;
    }

    auto &serviceProvider = GlEngine::Engine::GetInstance().GetServiceProvider();
    serviceProvider.RegisterService<GlEngine::IConfigProvider>(f_config);
    return f_config;
}
