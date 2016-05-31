#pragma once

#include "IComponent.h"
#include "Window.h"

namespace GlEngine
{
    class WindowManager;
    class GlController;

    class Engine : public IComponent
    {
    private:
        Engine();
        ~Engine();

        static Engine _instance;

    public:
        static constexpr Engine &GetInstance()
        {
            return _instance;
        }

        bool Initialize() override;
        void Shutdown() override;

        WindowManager &GetWindowManager();
        GlController &GetGlController();

        void MessageLoop();
        void RenderFrame();
    };
}
