#pragma once

#include "ILogger.h"
#include "IComponent.h"
#include <fstream>

namespace GlEngine
{
    class FileLogger : public ILogger, public IComponent
    {
    public:
        FileLogger(const char *const filename);
        FileLogger(const char *const path, const char *const filename);
        ~FileLogger();

        bool Initialize();
        void Shutdown();

        inline std::mutex &GetMutex()
        {
            return _mutex;
        }

    private:
        const char *const _path,
                   *const _filename;
        std::ofstream _logStream;
        std::mutex _mutex;

        bool LogImpl(LogType type, const char *const message) override;
    };
}
