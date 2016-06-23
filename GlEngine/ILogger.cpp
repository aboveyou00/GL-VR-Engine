#include "stdafx.h"
#include "ILogger.h"
#include "TimeUtils.h"
#include <iostream>

namespace GlEngine
{
    ILogger::ILogger()
    {
    }
    ILogger::~ILogger()
    {
    }

    rt_mutex ILogger::_consoleMutex;

    bool ILogger::HandleConsoleFlag()
    {
        return true;
    }

    const char *const ILogger::getTimestamp()
    {
        return Util::getTimestamp();
    }
}
