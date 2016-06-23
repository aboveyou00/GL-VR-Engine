#pragma once

#include "IComponent.h"
#include "TileRPGGameLoop.h"
#include "GameLogic.h"

namespace GlEngine
{
    class Window;
    class GlRenderTarget;
    class ILogger;
}

namespace TileRPG
{
    class TileRPGGame : public GlEngine::IComponent
    {
    public:
        TileRPGGame();
        ~TileRPGGame();

        bool Initialize();
        void Shutdown();

        void MessageLoop();

        inline TileRPGGameLoop &GetGameLoop()
        {
            return _loop;
        }

        inline GlEngine::Window &GetWindow()
        {
            return *_window;
        }
        inline GlEngine::GlRenderTarget &GetRenderTarget()
        {
            return *_renderTarget;
        }

    private:
        TileRPGGameLoop _loop;

        GlEngine::ILogger *logger;

        bool createWindow();
        void destroyWindow();
        GlEngine::Window *_window;
        GlEngine::GlRenderTarget *_renderTarget;
    };
}
