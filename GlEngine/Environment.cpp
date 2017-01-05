#include "stdafx.h"
#include "Environment.h"
#include "TimeUtils.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Environment::Environment()
        {
        }
        Environment::~Environment()
        {
        }

        float Environment::GetGameTime()
        {
            return Util::getGameMillis() / 1000.0f;
        }
    }
}
