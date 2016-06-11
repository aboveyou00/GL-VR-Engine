#pragma once

#include "Vector.h"

namespace GlEngine
{
	class TranformedGraphicsObject
	{
		TranformedGraphicsObject();
		~TranformedGraphicsObject();

		Vector<3> position;
	};
}