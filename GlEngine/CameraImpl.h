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
			Vector<3> center;
			Vector<3> up;
			double left = -1, right = 1, top = 1, bottom = -1, nearVal = 0, farVal = 100;

			Matrix<4, 4> view;
			Matrix<4, 4> proj;

			void ApplyView();
			void ApplyProjection();
		};
	}
}