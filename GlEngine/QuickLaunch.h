#pragma once

namespace GlEngine
{
    class Window;
    class RenderTarget;
    class ILogger;
    class IConfigProvider;
    class QuickLaunchLoop;
    class Frame;

    class QuickLaunch : public GlEngine::IInitializable
    {
    public:
        QuickLaunch(std::string name, std::string logName, std::string configName, unsigned frameRate = 200);
        ~QuickLaunch();

        void SetInitialFrame(Frame *frame);

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual std::string name() override;

        void MessageLoop();

        QuickLaunchLoop &GetLoop();
        GlEngine::Window &GetWindow();

    private:
        std::string _name, _logName, _configName;
        QuickLaunchLoop *_loop;

        GlEngine::ILogger *logger = nullptr;
        GlEngine::IConfigProvider *config = nullptr;

        bool createWindow();
        void destroyWindow();
        GlEngine::Window *_window = nullptr;

        GlEngine::ILogger *registerLogger();
        GlEngine::IConfigProvider *registerConfig();
    };

}
