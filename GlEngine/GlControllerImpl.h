#pragma once

#include "IGameComponent.h"
#include "Camera.h"

namespace GlEngine
{
    namespace Impl
    {
        class ENGINE_SHARED GlControllerImpl : public IComponent
        {
        public:
            GlControllerImpl();
            ~GlControllerImpl();

            bool Initialize();
            void Shutdown();

            inline std::mutex &GetMutex()
            {
                return renderTargetMutex;
            }

            const char *name() override;

        private:
            std::mutex renderTargetMutex;
        };
    }
}
