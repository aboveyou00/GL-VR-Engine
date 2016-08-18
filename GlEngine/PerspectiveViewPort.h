#pragma once

#include "ViewPort.h"

namespace GlEngine
{
	class ENGINE_SHARED PerspectiveViewPort : public ViewPort
	{
	public:
		PerspectiveViewPort();
		~PerspectiveViewPort();

		virtual void Push() override;
		virtual void Pop() override;

		virtual void SetNear(float nearVal);
		virtual void SetFar(float farVal);
	
	protected:
		float nearVal = 1.f;
		float farVal = 100.f;
	};
}
