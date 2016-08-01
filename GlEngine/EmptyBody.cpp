#include "stdafx.h"
#include "EmptyBody.h"

namespace GlEngine
{

	EmptyBody::EmptyBody()
	{
	}
	EmptyBody::~EmptyBody()
	{
	}

	const char * EmptyBody::name()
	{
		return "EmptyBody";
	}

	bool EmptyBody::Collide(Body* other, bool trySwitched)
	{
		return Body::Collide(other, trySwitched);
	}
}