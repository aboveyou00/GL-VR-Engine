#pragma once

#include "IComponent.h"
#include "ServiceProvider.h"
#include "Window.h"

namespace GlEngine
{
    class WindowManager;
    class GlController;

    class ENGINE_SHARED Engine : public IComponent
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
        inline ServiceProvider &GetServiceProvider()
        {
            return _services;
        }

        void MessageLoop();
        void RenderFrame();

    private:
        ServiceProvider _services;
    };
}
