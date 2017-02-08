#pragma once

#include "IGameComponent.h"
#include "Camera.h"
#include "GameLoop.h"
#include "GraphicsContext.h"

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

            virtual bool Initialize();
            virtual void Shutdown();

            void AddGraphicsContext(GraphicsContext *graphicsContext);

            rt_mutex &GetMutex();

            virtual std::string name() override;

        private:
            rt_mutex _lock;
            GameLoop _loop;

            static const int MAX_GRAPHICS_CONTEXTS = 16;
            GraphicsContext *graphicsContexts[MAX_GRAPHICS_CONTEXTS];
            size_t graphicsContextCount = 0;

            Window *dummyWindow;
            void MakeDefaultContext();
            bool LoadGlewExtensions();

            bool InitializeGraphicsThread();
            void Tick(float delta);
            void ShutdownGraphicsThread();
        };
    }
}
