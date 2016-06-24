#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace GlEngine
{
	class ENGINE_SHARED GameObject
	{
	public:
        GameObject(Vector<3> position = Vector<3> { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
		~GameObject();

		Vector<3> position;
		Matrix<4, 4> orientation;
	};
}
