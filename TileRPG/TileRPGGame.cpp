#include "stdafx.h"
#include "TileRPGGame.h"

#include "Engine.h"
#include "WindowManager.h"
#include "GraphicsContext.h"
#include "TransformedGraphicsObject.h"
#include "Camera.h"

#include "GlRenderTarget.h"
#include "OpenGl.h"

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

		auto & graphicsContext = * new GlEngine::GraphicsContext();
		
        //_window->SetFullscreen(true);
        _renderTarget = new GlEngine::GlRenderTarget(_window);
        if (!_renderTarget->Initialize())
        {
            engine.Shutdown(); //This will call _window.Shutdown(), we don't have to
            return false;
        }

		GlEngine::GameObject gameObject;
		auto graphicsObject = new GlEngine::GraphicsObject();
		graphicsContext.Register(&gameObject, graphicsObject);

		GlEngine::Camera camera;

		camera.SetEye({ 0, 0, 0 });
		camera.SetTarget({ 0, 0, 1 });
		camera.SetUp({ 0, 1, 0 });

		graphicsContext.camera = camera;

        glClearColor(1.f, 0.f, 0.f, 1.f);
        
		graphicsContext.AddRenderTarget(_renderTarget);

        _window->Show();
		graphicsContext.Update();
		graphicsContext.Render();
		
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
        if (!_loop.Initialize()) { Shutdown(); return false; }
        if (!createWindow()) { Shutdown(); return false; }
        return true;
    }
    void TileRPGGame::Shutdown()
    {
        destroyWindow();
        _loop.Shutdown();
    }

    void TileRPGGame::MessageLoop()
    {
        auto &engine = GlEngine::Engine::GetInstance();
        engine.MessageLoop();
    }
}
