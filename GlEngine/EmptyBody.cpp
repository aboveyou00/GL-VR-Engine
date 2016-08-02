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

	bool EmptyBody::Collide(Body*, bool)
	{
		return false;
	}
	float EmptyBody::MinX()
	{
		return 0.0f;
	}
	float EmptyBody::MaxX()
	{
		return 0.0f;
	}
	float EmptyBody::MinY()
	{
		return 0.0f;
	}
	float EmptyBody::MaxY()
	{
		return 0.0f;
	}
	float EmptyBody::MinZ()
	{
		return 0.0f;
	}
	float EmptyBody::MaxZ()
	{
		return 0.0f;
	}
}