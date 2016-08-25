#include "stdafx.h"
#include "Environment.h"
#include "TimeUtils.h"

namespace GlEngine
{
	Environment::Environment()
	{
	}
	Environment::~Environment()
	{
	}

	float Environment::GetGameTime()
	{
		return Util::getGameMillis() / 1000.0;
	}
}
