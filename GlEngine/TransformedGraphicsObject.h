#pragma once

#include "stdafx.h" //This header isn't included in any cpp files yet, so ENGINE_SHARED isn't defined yet. (Essentially, this header is not compiled in any way, shape, or form)
#include "Vector.h"

namespace GlEngine
{
	class ENGINE_SHARED TranformedGraphicsObject
	{
		TranformedGraphicsObject();
		~TranformedGraphicsObject();

		Vector<3> position;
	};
}
