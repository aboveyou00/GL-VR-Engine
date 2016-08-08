#pragma once
#include "ViewPort.h"

namespace GlEngine
{
	class ENGINE_SHARED OrthoViewPort : ViewPort
	{
	public:
		OrthoViewPort();		
		~OrthoViewPort();

		virtual void Push() override;
		virtual void Pop() override;

		virtual void SetNear(float nearVal);
		virtual void SetFar(float farVal);

	protected:
		float nearVal = 0.1f;
		float farVal = 100.f;
	};
}