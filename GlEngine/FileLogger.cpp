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
            Log(LogType::FatalError, "FileLogger.Initialize() failed to open log file [%s]", fullPath);
            return false;
        }
        Log(LogType::Info, "FileLogger.Initialize() opened log file [%s] for writing", fullPath);

        Log(LogType::Info, "FileLogger.Initialize() successful");
        return true;
    }
    void FileLogger::Shutdown()
    {
        if (_logStream) _logStream.flush();
        _logStream.close();
    }

    const char *FileLogger::name()
    {
        return "FileLogger";
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
