#pragma once

#include "IComponent.h"
#include "TileRPGGameLoop.h"

namespace GlEngine
{
    class Window;
    class RenderTarget;
    class GraphicsContext;
    class ILogger;
    class IConfigProvider;
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

        std::string name() override;

        void MessageLoop();

        inline TileRPGGameLoop &GetGameLoop()
        {
            return _loop;
        }

        inline GlEngine::Window &GetWindow()
        {
            return *_window;
        }

    private:
        TileRPGGameLoop _loop;

        GlEngine::ILogger *logger = nullptr;
        GlEngine::IConfigProvider *config = nullptr;

        bool createWindow();
        void destroyWindow();
        GlEngine::Window *_window = nullptr;
        GlEngine::GraphicsContext *_gfxContext = nullptr;

        GlEngine::ILogger *registerLogger();
        GlEngine::IConfigProvider *registerConfig();
    };
}
