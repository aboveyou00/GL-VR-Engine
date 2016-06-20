#include "stdafx.h"
#include "Engine.h"
#include "WindowManager.h"
#include "GlRenderTarget.h"
#include "OpenGl.h"

#include "GraphicsContext.h"
#include "GraphicsObject.h"
#include "TransformedGraphicsObject.h"

int main(int argc, char **argv)
{
    argc; argv;

    int result = -1;
    auto &engine = GlEngine::Engine::GetInstance();
    if (engine.Initialize())
    {
		GlEngine::GraphicsObject gObj;
		GlEngine::TransformedGraphicsObject tgObj(gObj);
		GlEngine::GraphicsContext gContext;

		gContext.AddGraphicsObject(&tgObj);

        auto window = engine.GetWindowManager().Create();
        if (window != nullptr)
        {
            //window->SetFullscreen(true);
            GlEngine::GlRenderTarget renderTarget(window);
			renderTarget.SetGraphicsContext(&gContext);

            if (renderTarget.Initialize())
            {
				glClearColor(0.f, 0.f, 0.f, 1.f);
				glClear(GL_COLOR_BUFFER_BIT);

				window->Show();
				renderTarget.Render();
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
