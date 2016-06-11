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

			std::mutex renderTargetMutex;

            bool Initialize();
            void Shutdown();
        };
    }
}