#include "stdafx.h"
#include "GraphicsControllerImpl.h"
#include "Matrix.h"
#include "OpenGl.h"

namespace GlEngine
{
    namespace Impl
    {
        GraphicsControllerImpl::GraphicsControllerImpl()
        {
        }
        GraphicsControllerImpl::~GraphicsControllerImpl()
        {
        }

        bool GraphicsControllerImpl::Initialize()
        {
            return true;
        }
        void GraphicsControllerImpl::Shutdown()
        {
        }

        const char *GraphicsControllerImpl::name()
        {
            return "GlControllerImpl";
        }
    }
}
