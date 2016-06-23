#pragma once

#include "ILogger.h"

namespace GlEngine
{
    class ENGINE_SHARED ConsoleLogger : public ILogger
    {
    public:
        ConsoleLogger();
        ~ConsoleLogger();

    private:
        bool HandleConsoleFlag() override;
        bool LogImpl(LogType type, const char *const message) override;
    };
}
