#include "stdafx.h"
#include "GraphicsController.h"
#include "GraphicsControllerImpl.h"

namespace GlEngine
{
    GraphicsController::GraphicsController()
        : pimpl(new Impl::GraphicsControllerImpl())
    {
    }
    GraphicsController::~GraphicsController()
    {
        if (pimpl != nullptr)
        {
            delete pimpl;
            pimpl = nullptr;
        }
    }

    GraphicsController GraphicsController::_instance;

    bool GraphicsController::Initialize()
    {
        return pimpl->Initialize();
    }
    void GraphicsController::Shutdown()
    {
        pimpl->Shutdown();
    }

    const char *GraphicsController::name()
    {
        return "GlController";
    }
}
