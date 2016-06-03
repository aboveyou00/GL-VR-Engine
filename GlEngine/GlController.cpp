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
        Shutdown();
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
}
