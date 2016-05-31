#pragma once

#include "IGameComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class GlControllerImpl : public IGameComponent
        {
        public:
            GlControllerImpl();
            ~GlControllerImpl();

            bool Initialize();
            void Shutdown();
        };
    }
}
