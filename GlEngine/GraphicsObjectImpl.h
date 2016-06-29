#pragma once

#include "OpenGl.h"
#include "VbObject.h"

namespace GlEngine
{
	namespace Impl
	{
		class ENGINE_SHARED GraphicsObjectImpl
		{
		public:
			GraphicsObjectImpl();
			~GraphicsObjectImpl();

			VbObject arrayVbo;
            VbObject elementVbo;

			void Render();
		};
	}
}
