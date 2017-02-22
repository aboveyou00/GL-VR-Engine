#pragma once

#include "GameLoop.h"

namespace GlEngine
{
    class Window;
    class RenderTarget;

    namespace Impl
    {
        class ENGINE_SHARED GraphicsControllerImpl : public IInitializable
        {
        public:
            GraphicsControllerImpl();
            ~GraphicsControllerImpl();

            virtual bool Initialize() override;
            virtual void Shutdown() override;

            void AddRenderTarget(RenderTarget *target);

            rt_mutex &GetMutex();

            virtual std::string name() override;

        private:
            rt_mutex _lock;
            GameLoop _loop;
            HDC _hdc;
            HGLRC _hglrc;

            void CreateDummyWindow();

            std::vector<RenderTarget*> renderTargets;

            Window *dummyWindow;
            void MakeDefaultContext();
            bool LoadGlewExtensions();

            bool InitializeGraphicsThread();
            void Tick(float delta);
            void ShutdownGraphicsThread();
        };
    }
}
