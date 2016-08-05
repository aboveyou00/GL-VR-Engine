#pragma once

#include "Vector.h"

namespace GlEngine
{
	class ENGINE_SHARED Force
	{
	public:
		Force(Vector<3> component);
		~Force();

		Vector<3> component;
	};
}