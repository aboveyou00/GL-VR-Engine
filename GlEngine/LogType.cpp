#include "stdafx.h"
#include "LogType.h"

namespace GlEngine
{
    const char *const MakeReadableLogType(LogType type)
    {
        if (type == LogType::Console) return "Console";

        if ((type & LogType::Console) != LogType::Ignore) type &= ~LogType::Console;

        switch (type)
        {
        case GlEngine::LogType::Ignore:
            return "Ignore";
        case GlEngine::LogType::Info:
            return "Info";
        case GlEngine::LogType::Warning:
            return "Warning";
        case GlEngine::LogType::Error:
            return "Error";
        case GlEngine::LogType::FatalError:
            return "FatalError";
        default:
            return "%%ERROR<MakeReadableLogType>%%";
        }
    }
}
