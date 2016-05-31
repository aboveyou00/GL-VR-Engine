#include "stdafx.h"
#include "Engine.h"
#include "WindowManager.h"
#include "GlRenderTarget.h"

int main(int argc, char **argv)
{
    argc; argv; //Don't complain!

    int result = -1;
    auto &engine = GlEngine::Engine::GetInstance();
    if (engine.Initialize())
    {
        auto window = engine.GetWindowManager().Create();
        if (window != nullptr)
        {
            window->SetFullscreen(true);
            GlEngine::GlRenderTarget renderTarget(window);
            if (renderTarget.Initialize())
            {
                window->Show();

                engine.MessageLoop();

                renderTarget.Shutdown();
                result = 0;
            }
        }

        engine.Shutdown(); //engine.Shutdown will clean up the window
    }

    return result;
}
