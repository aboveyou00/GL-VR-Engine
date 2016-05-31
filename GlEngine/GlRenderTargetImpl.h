#pragma once

#include "IComponent.h"
#include "OpenGl.h"

namespace GlEngine
{
    class Window;

    namespace Impl
    {
        class GlRenderTargetImpl : public IComponent
        {
        public:
            GlRenderTargetImpl(Window *window);
            ~GlRenderTargetImpl();

            bool Initialize();
            void Shutdown();

        private:
            Window *_window;
        };
    }
}
