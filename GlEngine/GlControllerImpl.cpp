#include "stdafx.h"
#include "GlControllerImpl.h"
#include "Matrix.h"
#include "OpenGl.h"

namespace GlEngine
{
    namespace Impl
    {
        GlControllerImpl::GlControllerImpl()
        {
        }
        GlControllerImpl::~GlControllerImpl()
        {
        }

        bool GlControllerImpl::Initialize()
        {
            return true;
        }
        void GlControllerImpl::Shutdown()
        {
        }

        const char *GlControllerImpl::name()
        {
            return "GlControllerImpl";
        }
    }
}
