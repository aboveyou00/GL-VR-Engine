#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace GlEngine
{
	namespace Impl
	{
		class ENGINE_SHARED CameraImpl
		{
		public:
			CameraImpl();
			~CameraImpl();

			Vector<3> eye;
			Vector<3> target;
			Vector<3> up;

			Matrix<4, 4> view;

			void Push();
			void Pop();
		};
	}
}