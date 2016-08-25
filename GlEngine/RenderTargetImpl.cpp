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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
        void RenderTargetImpl::Push(RenderTargetLayer layer)
		{
            glEnable(GL_TEXTURE_2D);
            if (layer == RenderTargetLayer::Layer3dOpaque || layer == RenderTargetLayer::Layer3dTransluscent)
            {
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_CULL_FACE);
                glDepthFunc(GL_LEQUAL);
            }
            else if (layer == RenderTargetLayer::Layer2d)
            {
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_CULL_FACE);
                glDepthFunc(GL_NONE);
                MatrixStack::ModelView.push(Matrix<4, 4>::Identity());
            }

			ViewPort* viewPort = this->viewPorts[(int)layer - (int)std::numeric_limits<RenderTargetLayer>::min()];
			if (viewPort != nullptr)
				viewPort->Push();
		}
		void RenderTargetImpl::Pop(RenderTargetLayer layer)
		{
            if (layer == RenderTargetLayer::Layer2d)
            {
                MatrixStack::ModelView.pop();
            }

			ViewPort* viewPort = this->viewPorts[(int)layer - (int)std::numeric_limits<RenderTargetLayer>::min()];
			if (viewPort != nullptr)
				viewPort->Pop();
		}

		void RenderTargetImpl::Flip()
		{
		}

		void RenderTargetImpl::SetViewPort(RenderTargetLayer layer, ViewPort * viewPort)
		{
            auto idx = (int)layer - (int)std::numeric_limits<RenderTargetLayer>::min();
            if (idx < 0) return;

			ViewPort* mViewPort = this->viewPorts[idx];
			if (mViewPort != nullptr)
				delete mViewPort;
			this->viewPorts[(int)layer - (int)std::numeric_limits<RenderTargetLayer>::min()] = viewPort;
		}
    }
}
