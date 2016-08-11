#include "stdafx.h"
#include "RenderTargetImpl.h"
#include "MatrixStack.h"
#include <chrono>

namespace GlEngine
{
    namespace Impl
    {
		RenderTargetImpl::RenderTargetImpl()
		{
		}
        RenderTargetImpl::~RenderTargetImpl()
        {
        }

        bool RenderTargetImpl::Initialize()
        {
			return true;
        }

        void RenderTargetImpl::Shutdown()
        {
        }

        const char *RenderTargetImpl::name()
        {
            return "RenderTargetImpl";
        }

		void RenderTargetImpl::MakeCurrentTarget()
		{
		}

        void RenderTargetImpl::Prepare()
        {
        }
        void RenderTargetImpl::Push()
		{
			viewPort->Push();
		}
		void RenderTargetImpl::Pop()
		{
			viewPort->Pop();
		}

		void RenderTargetImpl::Flip()
		{
		}

		void RenderTargetImpl::SetViewPort(ViewPort * viewPort)
		{
			this->viewPort = viewPort;
		}
    }
}
