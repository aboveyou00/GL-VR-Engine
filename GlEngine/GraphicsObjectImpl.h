#pragma once

namespace GlEngine
{
	namespace Impl
	{
		class ENGINE_SHARED GraphicsObjectImpl
		{
		public:
			GraphicsObjectImpl();
			~GraphicsObjectImpl();

			int magic = 0xDEADBEEF;

			void Render();
		};
	}
}