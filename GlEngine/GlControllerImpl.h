#pragma once

#include "IGameComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class GlControllerImpl : public IComponent
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

        private:
            std::mutex renderTargetMutex;
        };
    }
}
