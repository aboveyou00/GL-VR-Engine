#include "stdafx.h"
#include "FileConfigProvider.h"
#include "StringUtils.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"

namespace GlEngine
{
    FileConfigProvider::FileConfigProvider(const char *const path, const char *const filename)
        : _path(path), _filename(filename)
    {
    }
    FileConfigProvider::~FileConfigProvider()
    {
        Shutdown();
    }

    //Preload helper methods:
    static bool openFile(std::ifstream *file, const char *const filename);
    static bool readKeys(std::ifstream *file, GlEngine::FileConfigProvider &kvps);
    static bool parseLine(const char *const line, const char *&key, const char *&val);
    static bool closeFile(std::ifstream *file);

    static const char *const extractKey(const char *&ptr);
    static const char *const extractValue(const char *&ptr, const char *const key);
    static bool ensureNothingElse(const char *&ptr, const char *const key, const char *const val);

    bool FileConfigProvider::Initialize()
    {
        auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger.Log(LogType::Info, "Initializing FileConfigProvider...");

        std::ifstream file;
        if (!openFile(&file, _filename))
        {
            logger.Log(LogType::Warning, "FileConfigProvider.Initialize() exited with no configuration values.");
            return true;
        }
        if (!readKeys(&file, *this))
        {
            logger.Log(LogType::FatalError, "FileConfigProvider.Initialize() failed to read configuration file.");
            file.close();
            return false;
        }
        if (!closeFile(&file))
        {
            logger.Log(LogType::Warning, "FileConfigProvider.Initialize() exited without releasing file handle.");
            return true;
        }

        logger.Log(LogType::Info, "FileConfigProvider.Initialize() successful.");
        return true;
    }
    void FileConfigProvider::Shutdown()
    {
        auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger.Log(LogType::Info, "~Shutting down FileConfigProvider...");
    }

    const char *FileConfigProvider::name()
    {
        return "FileConfigProvider";
    }

    bool FileConfigProvider::IsFull() const
    {
        for (size_t q = 0; q < MAX_KVPS; q++)
        {
            if (_pairs[q].GetKey() == nullptr || _pairs[q].GetKey()[0] == '\0') return false;
        }
        return true;
    }
    const char *const FileConfigProvider::operator[](const char *const key) const
    {
        for (size_t q = 0; q < MAX_KVPS; q++)
        {
            if (strcmp(key, _pairs[q].GetKey()) == 0) return _pairs[q].GetValue();
        }
        return nullptr;
    }

    bool FileConfigProvider::AddUnique(const char *const key, const char *const value)
    {
        int firstAvailableIndex = -1;
        for (size_t q = 0; q < MAX_KVPS; q++)
        {
            auto pk = _pairs[q].GetKey();
            if (pk == nullptr || pk[0] == '\0')
            {
                if (firstAvailableIndex == -1) firstAvailableIndex = q;
                continue;
            }
            if (strcmp(key, _pairs[q].GetKey()) == 0)
            {
                auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
                logger.Log(LogType::Warning, "Tried to add duplicate key to FileConfigProvider: {%s: %s}", key, value);
                return false;
            }
        }
        if (firstAvailableIndex == -1)
        {
            auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            logger.Log(LogType::Warning, "Tried to add key/value pair to a full FileConfigProvider: {%s: %s}", key, value);
            return false;
        }
        _pairs[firstAvailableIndex] = Util::KeyValuePair(key, value);
        return true;
    }

    bool openFile(std::ifstream *file, const char *const filename)
    {
        file->open(filename, std::ios::in);
        if (file->fail() || !*file)
        {
            auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            logger.Log(LogType::Warning, "Could not open configuration file [%s]", filename);
            return false;
        }
        return true;
    }

    bool readKeys(std::ifstream *file, GlEngine::FileConfigProvider &kvps)
    {
        static const int BUFF_SIZE = GlEngine::Util::KeyValuePair::MAX_KEY_SIZE + GlEngine::Util::KeyValuePair::MAX_VALUE_SIZE + 128;
        char line[BUFF_SIZE];
        while (file->getline(line, sizeof(line)), !file->fail())
        {
            const char *key, *val;
            if (!parseLine(line, key, val)) continue;
            if (!kvps.AddUnique(key, val)) return false;
        }
        return true;
    }

    bool parseLine(const char *const line, const char *&key, const char *&val)
    {
        const char *ptr = line;

        //Read key
        key = extractKey(ptr);
        if (key == nullptr) return false;

        //Read value
        val = extractValue(ptr, key);
        if (val == nullptr) return false;

        //Make sure there's nothing else on the line
        if (!ensureNothingElse(ptr, key, val)) return false;

        return true;
    }
    const char *const extractKey(const char *&ptr)
    {
        static char buff[Util::KeyValuePair::MAX_KEY_SIZE];
        if (!Util::extractToken(buff, sizeof(buff), ptr)) return nullptr;
        return buff;
    }
    const char *const extractValue(const char *&ptr, const char *const key)
    {
        static char buff[Util::KeyValuePair::MAX_VALUE_SIZE];
        if (!Util::extractToken(buff, sizeof(buff), ptr))
        {
            auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            logger.Log(LogType::Error, "Found configuration key with an invalid value/no value: [%s]", key);
            return nullptr;
        }
        return buff;
    }
    bool ensureNothingElse(const char *&ptr, const char *const key, const char *const val)
    {
        auto err = Util::extractToken(ptr);
        if (err != nullptr)
        {
            auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            logger.Log(LogType::Error, "Found configuration key with several values: [%s]. First value: [%s]", key, val);
            return false;
        }
        return true;
    }

    bool closeFile(std::ifstream *file)
    {
        file->close();
        if (file->is_open())
        {
            auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            logger.Log(LogType::Error, "Could not close configuration file after reading it. Continuing...");
            return false;
        }
        return true;
    }
}
