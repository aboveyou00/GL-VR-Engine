#pragma once

#include "IInitializable.h"
#include "SandboxLoop.h"

namespace GlEngine
{
    class Window;
    class RenderTarget;
    class ILogger;
    class IConfigProvider;
}

class Sandbox : GlEngine::IInitializable
{
public:
    Sandbox();
    ~Sandbox();

    virtual bool Initialize() override;
    virtual void Shutdown() override;

    virtual std::string name() override;

    void MessageLoop();

    inline SandboxLoop &GetLoop()
    {
        return _loop;
    }

    inline GlEngine::Window &GetWindow()
    {
        return *_window;
    }

private:
    SandboxLoop _loop;

    GlEngine::ILogger *logger = nullptr;
    GlEngine::IConfigProvider *config = nullptr;

    bool createWindow();
    void destroyWindow();
    GlEngine::Window *_window = nullptr;

    GlEngine::ILogger *registerLogger();
    GlEngine::IConfigProvider *registerConfig();
};
