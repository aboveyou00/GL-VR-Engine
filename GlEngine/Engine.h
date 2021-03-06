#pragma once

#include "IInitializable.h"
#include "EventQueue.h"
#include "ServiceProvider.h"
#include "Window.h"
#include "QuickLaunch.h"

#define THIS_ENGINE (GlEngine::Engine::GetInstance())

namespace GlEngine
{
    class WindowManager;
    class GraphicsController;
    class AudioController;

    class ENGINE_SHARED Engine : public IInitializable
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

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        WindowManager &GetWindowManager();
        GraphicsController &GetGraphicsController();
        AudioController &GetAudioController();
        inline Events::EventQueue &GetEventQueue()
        {
            return _events;
        }
        inline ServiceProvider &GetServiceProvider()
        {
            return _services;
        }

        rt_mutex &GetMutex();

        virtual std::string name() override;

        void MessageLoop();

        template <typename T, typename... TArgs>
        int QuickLaunchFrame(std::string name, std::string logFile, std::string configFile, unsigned frameRate, TArgs... args)
        {
            auto t = new T(args...);
            return QuickLaunchFrame(name, logFile, configFile, frameRate, t);
        }
        int QuickLaunchFrame(std::string name, std::string logFile, std::string configFile, unsigned frameRate, Frame *frame);

    private:
        Events::EventQueue _events;
        ServiceProvider _services;
    };
}
