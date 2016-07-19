#include "stdafx.h"
#include "GlController.h"
#include "GlControllerImpl.h"

namespace GlEngine
{
    GlController::GlController()
        : pimpl(new Impl::GlControllerImpl())
    {
    }
    GlController::~GlController()
    {
        if (pimpl != nullptr)
        {
            delete pimpl;
            pimpl = nullptr;
        }
    }

    GlController GlController::_instance;

    bool GlController::Initialize()
    {
        return pimpl->Initialize();
    }
    void GlController::Shutdown()
    {
        pimpl->Shutdown();
    }

    std::mutex &GlController::GetMutex()
    {
        return pimpl->GetMutex();
    }

    const char *GlController::name()
    {
        return "GlController";
    }
}
