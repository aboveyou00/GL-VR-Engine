#include "stdafx.h"
#include "TileRPGGame.h"

#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsContext.h"
#include "WindowRenderTarget.h"
//#include "TransformedGraphicsObject.h"

#include "PerspectiveViewPort.h"
#include "OrthoViewPort.h"
#include "Camera.h"

#include "FileLogger.h"
#include "FileConfigProvider.h"

//#include "ObjGraphicsObject.h"
//#include "FbxGraphicsObject.h"

//#include "TextureRenderTarget.h"

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

        if (config->GetValueWithDefault("Fullscreen", true)) _window->SetFullscreen(true);

        _gfxContext = new GlEngine::GraphicsContext(&_loop.GetFrameStack());

        GlEngine::RenderTarget* _renderTarget = new GlEngine::WindowRenderTarget(_window);
        
        auto viewport3d = new GlEngine::PerspectiveViewPort();
        auto viewport2d = new GlEngine::OrthoViewPort();
        _renderTarget->SetViewPort(GlEngine::RenderTargetLayer::Layer3dOpaque, viewport3d);
        _renderTarget->SetViewPort(GlEngine::RenderTargetLayer::Layer3dTransluscent, viewport3d);
        _renderTarget->SetViewPort(GlEngine::RenderTargetLayer::Layer2d, viewport2d);

        //GlEngine::RenderTarget* texRenderTarget = new GlEngine::TextureRenderTarget(200, 200);
        //texRenderTarget->SetViewPort(new GlEngine::PerspectiveViewPort());
        _gfxContext->AddRenderTarget(_renderTarget);
        //_gfxContext->AddRenderTarget(texRenderTarget);

        _gfxContext->camera.SetEye({ 0, 0, 0 });
        _gfxContext->camera.SetForward({ 0, 0, 1 });
        _gfxContext->camera.SetUp({ 0, 1, 0 });

        if (!_gfxContext->Initialize())
        {
            _renderTarget->Shutdown();
            engine.Shutdown(); //This will call _window.Shutdown(), we don't have to do it
            return false;
        }

        _window->Show();
        
        return true;
    }
    void TileRPGGame::destroyWindow()
    {
        if (_gfxContext != nullptr)
        {
            _gfxContext->Shutdown();
            delete _gfxContext;
            _gfxContext = nullptr;
        }

        auto &engine = GlEngine::Engine::GetInstance();
        engine.Shutdown();
    }

    bool TileRPGGame::Initialize()
    {
        logger = registerLogger();
        if (logger == nullptr) return false;
        
        logger->Log(GlEngine::LogType::InfoC, "Welcome to TileRPG! Beginning game initialization...");

        config = registerConfig();
        if (config == nullptr) return false;

        if (!createWindow())
        {
            logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize TileRPG. Aborting...");
            Shutdown();
            return false;
        }
        if (!_loop.Initialize())
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

        _loop.Shutdown();
        destroyWindow();
    }

    const char *TileRPGGame::name()
    {
        return "TileRPGGame";
    }

    void TileRPGGame::MessageLoop()
    {
        logger->Log(GlEngine::LogType::Info, "Beginning MessageLoop on thread [%s]...", this_thread_name());

        auto &engine = GlEngine::Engine::GetInstance();
        engine.MessageLoop();

        logger->Log(GlEngine::LogType::Info, "~Terminating MessageLoop...");
    }

    GlEngine::ILogger *TileRPGGame::registerLogger()
    {
        auto f_logger = new GlEngine::FileLogger("", "TileRPG.log");
        if (!f_logger->Initialize())
        {
            f_logger->Log(GlEngine::LogType::FatalErrorC, "Could not initialize file logger. Aborting");
            return nullptr;
        }

        auto &serviceProvider = GlEngine::Engine::GetInstance().GetServiceProvider();
        serviceProvider.RegisterService<GlEngine::ILogger>(f_logger);
        return f_logger;
    }
    GlEngine::IConfigProvider *TileRPGGame::registerConfig()
    {
        auto f_config = new GlEngine::FileConfigProvider("", "TileRPG.config");
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
