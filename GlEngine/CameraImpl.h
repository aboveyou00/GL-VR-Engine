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
			double left, right, top, bottom, nearVal, farVal;

			Matrix<4, 4> view;
			Matrix<4, 4> proj;

			void ApplyView();
			void ApplyProjection();
		};
	}
}