#pragma once

#include "Vector.h"

namespace GlEngine
{
	class Force
	{
	public:
		Force(Vector<3> component);
		~Force();

		Vector<3> component;
	};
}