#pragma once

#include "IComponent.h"
#include "SandboxLoop.h"

namespace GlEngine
{
    class Window;
    class RenderTarget;
    class GraphicsContext;
    class ILogger;
    class IConfigProvider;
}

class Sandbox : GlEngine::IComponent
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
    GlEngine::GraphicsContext *_gfxContext = nullptr;

    GlEngine::ILogger *registerLogger();
    GlEngine::IConfigProvider *registerConfig();
};
