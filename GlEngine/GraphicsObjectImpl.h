#pragma once

#include "OpenGl.h"

namespace GlEngine
{
	namespace Impl
	{
		class ENGINE_SHARED GraphicsObjectImpl
		{
		public:
			GraphicsObjectImpl();
			~GraphicsObjectImpl();

			GLuint vbo;

			void Render();
		};
	}
}