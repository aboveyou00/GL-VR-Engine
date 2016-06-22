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

    std::mutex ILogger::_consoleMutex;

    bool ILogger::HandleConsoleFlag()
    {
        return true;
    }

    const char *const ILogger::getTimestamp()
    {
        return Util::getTimestamp();
    }
}
