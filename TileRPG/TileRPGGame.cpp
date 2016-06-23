#include "stdafx.h"
#include "TileRPGGame.h"

#include "Engine.h"
#include "WindowManager.h"
#include "GlRenderTarget.h"
#include "OpenGl.h"

#include "FileLogger.h"

namespace TileRPG
{
    TileRPGGame::TileRPGGame()
    {
    }
    TileRPGGame::~TileRPGGame()
    {
        Shutdown();
    }

    bool TileRPGGame::createWindow()
    {
        auto &engine = GlEngine::Engine::GetInstance();
        if (!engine.Initialize()) return false;

        _window = engine.GetWindowManager().Create();
        if (_window == nullptr)
        {
            engine.Shutdown();
            return false;
        }

        //_window->SetFullscreen(true);
        _renderTarget = new GlEngine::GlRenderTarget(_window);
        if (!_renderTarget->Initialize())
        {
            engine.Shutdown(); //This will call _window.Shutdown(), we don't have to do it
            return false;
        }

        glClearColor(1.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        _window->Show();
		_renderTarget->Render();
        _renderTarget->Flip();

        return true;
    }
    void TileRPGGame::destroyWindow()
    {
        if (_renderTarget != nullptr)
        {
            _renderTarget->Shutdown();
            delete _renderTarget;
            _renderTarget = nullptr;
        }

        auto &engine = GlEngine::Engine::GetInstance();
        engine.Shutdown();
    }

    bool TileRPGGame::Initialize()
    {
        auto &serviceProvider = GlEngine::Engine::GetInstance().GetServiceProvider();
        auto f_logger = new GlEngine::FileLogger("", "TileRPG.log");
        logger = f_logger;
        if (!f_logger->Initialize())
        {
            f_logger->Log(GlEngine::LogType::Console, "Could not initialize file logger. Aborting");
            return false;
        }
        serviceProvider.RegisterService<GlEngine::ILogger>(f_logger);

        logger->Log(GlEngine::LogType::InfoC, "Welcome to TileRPG! Beginning game initialization...");

        if (!_loop.Initialize())
        {
            logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize TileRPG. Aborting...");
            Shutdown();
            return false;
        }
        if (!createWindow())
        {
            logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize TileRPG. Aborting...");
            Shutdown();
            return false;
        }

        logger->Log(GlEngine::LogType::InfoC, "TileRPG initialization successful. Beginning game.");
        return true;
    }
    void TileRPGGame::Shutdown()
    {
        logger->Log(GlEngine::LogType::Info, "~Shutting down TileRPGGame...");

        destroyWindow();
        _loop.Shutdown();
    }

    void TileRPGGame::MessageLoop()
    {
        logger->Log(GlEngine::LogType::Info, "Beginning TileRPGGame MessageLoop...");

        auto &engine = GlEngine::Engine::GetInstance();
        engine.MessageLoop();
    }
}
