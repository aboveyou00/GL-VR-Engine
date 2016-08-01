#pragma once

#include "Body.h"

namespace GlEngine
{
	class EmptyBody : public Body
	{
	public:
		EmptyBody();
		~EmptyBody();

		virtual const char *name() override;
		virtual bool Collide(Body* other, bool trySwitched = true) override;
	};
}