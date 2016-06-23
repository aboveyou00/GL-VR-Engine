#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace GlEngine
{
	namespace Impl
	{
		class CameraImpl
		{
		public:
			CameraImpl();
			~CameraImpl();

			Vector<3> eye;
			Vector<3> target;
			Vector<3> up;

			Matrix<4, 4> view;

			void Apply();
			
			void Push();
			void Pop();
		};
	}
}