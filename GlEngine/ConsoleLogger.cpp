#include "stdafx.h"
#include "ConsoleLogger.h"

namespace GlEngine
{
    ConsoleLogger::ConsoleLogger()
    {
    }
    ConsoleLogger::~ConsoleLogger()
    {
    }

    bool ConsoleLogger::HandleConsoleFlag()
    {
        return false;
    }
    bool ConsoleLogger::LogImpl(LogType type, const char *const message)
    {
        ScopedLock _lock(ILogger::GetConsoleMutex());
        if ((type & (LogType::Error | LogType::FatalError)) != LogType::Ignore) std::cerr << message << std::endl;
        else std::cout << message << std::endl;
        return true;
    }
}
