#pragma once

#include "IComponent.h"
#include "ServiceProvider.h"
#include "Window.h"
#include "EventQueue.h"

namespace GlEngine
{
    class WindowManager;
    class GlController;
    class AlController;

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
        AlController &GetAlController();
        inline Events::EventQueue &GetEventQueue()
        {
            return _events;
        }
        inline ServiceProvider &GetServiceProvider()
        {
            return _services;
        }

        void MessageLoop();

    private:
        ServiceProvider _services;
        Events::EventQueue _events;
    };
}
