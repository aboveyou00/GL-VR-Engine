#include "stdafx.h"
#include "GlRenderTargetImpl.h"

namespace GlEngine
{
    namespace Impl
    {
        GlRenderTargetImpl::GlRenderTargetImpl(Window *window)
            : _window(window)
        {
        }
        GlRenderTargetImpl::~GlRenderTargetImpl()
        {
        }

        bool GlRenderTargetImpl::Initialize()
        {
            return true;
        }
        void GlRenderTargetImpl::Shutdown()
        {
        }
    }
}
