#pragma once

#include "IGameComponent.h"
#include "Camera.h"

namespace GlEngine
{
    class Window;

    namespace Impl
    {
        class ENGINE_SHARED GraphicsControllerImpl : public IComponent
        {
        public:
            GraphicsControllerImpl();
            ~GraphicsControllerImpl();

            bool Initialize();
            void Shutdown();

            const char *name() override;

        private:
            Window * dummyWindow;
            void MakeDefaultContext();
            bool LoadGlewExtensions();
        };
    }
}
