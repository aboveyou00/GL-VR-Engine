#pragma once

namespace GlEngine
{
	class Body
	{
	public:
		Body();
		~Body();
		virtual const char *name();
		virtual bool Collide(Body* other, bool trySwitched = true);
	};
}