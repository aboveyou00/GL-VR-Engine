#include "stdafx.h"
#include "GlController.h"

namespace GlEngine
{
    GlController::GlController()
    {
    }
    GlController::~GlController()
    {
    }

    GlController GlController::_instance;

    bool GlController::Initialize()
    {
        return true;
    }
    void GlController::Shutdown()
    {
    }
}
