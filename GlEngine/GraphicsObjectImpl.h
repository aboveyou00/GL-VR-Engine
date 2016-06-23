#pragma once

namespace GlEngine
{
	namespace Impl
	{
		class GraphicsObjectImpl
		{
		public:
			GraphicsObjectImpl();
			~GraphicsObjectImpl();

			int magic = 0xDEADBEEF;

			void Render();
		};
	}
}