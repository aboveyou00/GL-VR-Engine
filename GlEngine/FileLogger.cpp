#include "stdafx.h"
#include "FileLogger.h"
#include "PathUtils.h"

namespace GlEngine
{
    FileLogger::FileLogger(const char *const filename)
        : FileLogger(nullptr, filename)
    {
    }
    FileLogger::FileLogger(const char *const path, const char *const filename)
        : _path(path), _filename(filename)
    {
    }
    FileLogger::~FileLogger()
    {
    }

    bool FileLogger::Initialize()
    {
        auto fullPath = Util::createLogFileName(_path, _filename);

        _logStream.open(fullPath, std::ios::trunc);
        if (_logStream.fail() || !_logStream)
        {
            Log(LogType::FatalErrorC, "FileLogger.Initialize() failed to open log file [%s]\n", fullPath);
            return false;
        }
        Log(LogType::InfoC, "FileLogger.Initialize() opened log file [%s] for writing\n", fullPath);

        Log(LogType::InfoC, "FileLogger.Initialize() successful\n");
        LogImpl(LogType::Info, "Hello, World!");
        return true;
    }
    void FileLogger::Shutdown()
    {
        if (_logStream) _logStream.flush();
        _logStream.close();
    }

    bool FileLogger::LogImpl(LogType, const char *const message)
    {
        if (!_logStream)
        {
            ScopedLock _lock(ILogger::GetConsoleMutex());
            std::cout << "NO_LOG_FILE!! " << message << std::endl;
            return false;
        }
        else
        {
            ScopedLock _lock(GetMutex());
            _logStream << message << std::endl;
            return true;
        }
    }
}
