#include "stdafx.h"
#include "TileRPGGame.h"

#include "Engine.h"
#include "WindowManager.h"
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

        //_window->SetFullscreen(true);
        _renderTarget = new GlEngine::GlRenderTarget(_window);
        if (!_renderTarget->Initialize())
        {
            engine.Shutdown(); //This will call _window.Shutdown(), we don't have to
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
