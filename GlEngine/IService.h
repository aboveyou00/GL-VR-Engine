#pragma once

#include "EngineShared.h"

namespace GlEngine
{
    class ENGINE_SHARED IService
    {
    public:
        IService();
        ~IService();

    private:
        virtual void __NoOp__();
    };
}
