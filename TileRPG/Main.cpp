#include "stdafx.h"
#include "Engine.h"
#include "WindowManager.h"
#include "GlRenderTarget.h"
#include "OpenGl.h"

int main(int argc, char **argv)
{
    argc; argv;

    int result = -1;
    auto &engine = GlEngine::Engine::GetInstance();
    if (engine.Initialize())
    {
        auto window = engine.GetWindowManager().Create();
        if (window != nullptr)
        {
            //window->SetFullscreen(true);
            GlEngine::GlRenderTarget renderTarget(window);
            if (renderTarget.Initialize())
            {
				glClearColor(1.f, 0.f, 0.f, 1.f);
				glClear(GL_COLOR_BUFFER_BIT);

                window->Show();
				renderTarget.Flip();

                engine.MessageLoop();

                renderTarget.Shutdown();
                result = 0;
            }
        }

        engine.Shutdown(); //engine.Shutdown will clean up the window
    }

    return result;
}
