#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace GlEngine
{
	class ENGINE_SHARED GameObject
	{
	public:
		GameObject();
		~GameObject();

		Vector<3> position;
		Matrix<4, 4> orientation;
	};
}