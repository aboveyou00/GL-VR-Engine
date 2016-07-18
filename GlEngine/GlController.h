#pragma once

#include "IComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class GlControllerImpl;
    }

    class ENGINE_SHARED GlController : public IComponent
    {
    private:
        GlController();
        ~GlController();

        static GlController _instance;

    public:
        inline static GlController &GetInstance()
        {
            return _instance;
        }

        bool Initialize();
        void Shutdown();

        std::mutex &GetMutex();

        const char *name() override;

        inline Impl::GlControllerImpl *GetImpl()
        {
            return pimpl;
        }

    private:
        Impl::GlControllerImpl *pimpl;
    };
}
