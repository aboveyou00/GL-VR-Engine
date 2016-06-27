#pragma once

#include "IService.h"
#include "LogType.h"
#include <stdio.h>

namespace GlEngine
{
    class ENGINE_SHARED ILogger : public IService
    {
    public:
        ILogger();
        ~ILogger();

        template <typename... TArgs>
        bool Log(LogType type, const char *const format, TArgs... args)
        {
            if (type == LogType::Ignore) return false;

            bool logConsole = false;
            if (HandleConsoleFlag() && (type & LogType::Console) != LogType::Ignore)
            {
                type &= ~LogType::Console;
                logConsole = true;
            }

            static const size_t BUFFER_SIZE = 512;
            static thread_local char buff1[BUFFER_SIZE];
            static thread_local char buff2[BUFFER_SIZE];
            sprintf_s(buff1, BUFFER_SIZE, format, args...);
            sprintf_s(buff2, BUFFER_SIZE, "%s [%-8s] [THREAD: %-8s] %s", getTimestamp(), MakeReadableLogType(type), this_thread_name(), buff1);

            if (logConsole)
            {
                ScopedLock _lock(_consoleMutex);
                if ((type & (LogType::Error | LogType::FatalError)) != LogType::Ignore) std::cerr << buff2 << std::endl;
                else std::cout << buff2 << std::endl;
                if (type == LogType::Ignore) return true;
            }
            return LogImpl(type, buff2);
        }

        inline static rt_mutex &GetConsoleMutex()
        {
            return _consoleMutex;
        }

    protected:
        virtual bool HandleConsoleFlag();
        virtual bool LogImpl(LogType type, const char *const message) = 0;

    private:
        static rt_mutex _consoleMutex;
        const char *const getTimestamp();
    };
}
