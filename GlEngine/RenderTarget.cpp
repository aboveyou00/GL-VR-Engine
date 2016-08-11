#include "stdafx.h"
#include "RenderTarget.h"

namespace GlEngine
{
	RenderTarget::RenderTarget()
		: pimpl()
	{
	}
	RenderTarget::~RenderTarget()
	{
		Shutdown();
		if (pimpl != nullptr)
		{
			delete pimpl;
			pimpl = nullptr;
		}
	}

	bool RenderTarget::Initialize()
	{
		return pimpl->Initialize();
	}
	void RenderTarget::Shutdown()
	{
		pimpl->Shutdown();
	}

	const char *RenderTarget::name()
	{
		return "GlRenderTarget";
	}
	void RenderTarget::SetViewPort(ViewPort * viewPort)
	{
		pimpl->SetViewPort(viewPort);
	}

	void RenderTarget::SetCurrent()
	{
		pimpl->MakeCurrentTarget();
	}

	bool RenderTarget::GetShouldRender()
	{
		return pimpl->GetShouldRender();
	}

	void RenderTarget::Prepare()
	{
		pimpl->Prepare();
	}
	void RenderTarget::Push()
	{
		pimpl->Push();
	}
	void RenderTarget::Pop()
	{
		pimpl->Pop();
	}

	void RenderTarget::Flip()
	{
		pimpl->Flip();
	}
}