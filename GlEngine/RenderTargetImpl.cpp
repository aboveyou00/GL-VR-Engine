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
			for (int i = 0; i < layerCount; i++)
				viewPorts[i] = nullptr;
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
			for (int i = 0; i < layerCount; i++)
			{
				if (viewPorts[i] != nullptr)
					delete viewPorts[i];
			}
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
		void RenderTargetImpl::PrePush()
		{
		}
        void RenderTargetImpl::Push(RenderTargetLayer layer)
		{
			ViewPort* viewPort = this->viewPorts[(int)layer - (int)std::numeric_limits<RenderTargetLayer>::min()];
			if (viewPort != nullptr)
				viewPort->Push();
		}
		void RenderTargetImpl::Pop(RenderTargetLayer layer)
		{
			ViewPort* viewPort = this->viewPorts[(int)layer - (int)std::numeric_limits<RenderTargetLayer>::min()];
			if (viewPort != nullptr)
				viewPort->Pop();
		}

		void RenderTargetImpl::Flip()
		{
		}

		void RenderTargetImpl::SetViewPort(RenderTargetLayer layer, ViewPort * viewPort)
		{
			ViewPort* mViewPort = this->viewPorts[(int)layer - (int)std::numeric_limits<RenderTargetLayer>::min()];
			if (mViewPort != nullptr)
				delete mViewPort;
			this->viewPorts[(int)layer - (int)std::numeric_limits<RenderTargetLayer>::min()] = viewPort;
		}
    }
}
