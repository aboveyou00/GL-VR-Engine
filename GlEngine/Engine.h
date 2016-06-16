#pragma once

#include "IComponent.h"
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
        Events::EventQueue &GetEventQueue();

        void MessageLoop();

    private:
        Events::EventQueue _events;
    };
}
