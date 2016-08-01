#include "stdafx.h"
#include "Body.h"

namespace GlEngine
{
	Body::Body()
	{
	}
	Body::~Body()
	{
	}
	const char * Body::name()
	{
		return nullptr;
	}
	bool Body::Collide(Body* other, bool trySwitched)
	{
		if (trySwitched)
			return other->Collide(this, false);
		return false;
	}
}