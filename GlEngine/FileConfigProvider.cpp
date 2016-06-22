#include "stdafx.h"
#include "FileConfigProvider.h"
#include "StringUtils.h"

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
        std::ifstream file;
        if (!openFile(&file, _filename))
        {
            //TODO: Log initialize failed
            //GameLogger::Current()->Log(LogType::FatalError, "ConfigReader.Initialize() failed.\n");
            return false;
        }
        if (!readKeys(&file, *this))
        {
            //TODO: Log initialize failed
            //GameLogger::Current()->Log(LogType::FatalError, "ConfigReader.Initialize() failed.\n");
            file.close();
            return false;
        }
        if (!closeFile(&file))
        {
            //TODO: Log initialize failed
            //GameLogger::Current()->Log(LogType::FatalError, "ConfigReader.Initialize() failed.\n");
            return false;
        }
        //TODO: Log initialize successful
        //GameLogger::Current()->Log(LogType::Process, "ConfigReader.Initialize() successful.\n");
        return true;
    }
    void FileConfigProvider::Shutdown()
    {
        //TODO: Log shutdown
        //GameLogger::Current()->Log(LogType::Process, "ConfigReader.Shutdown() successful.\n");
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
                //TODO: Log attempt at duplicate key.
                return false;
            }
        }
        if (firstAvailableIndex == -1)
        {
            //TODO: Log failed attempt because there was no space
            return false;
        }
        _pairs[firstAvailableIndex] = Util::KeyValuePair(key, value);
        return true;
    }

    bool openFile(std::ifstream *file, const char *const filename)
    {
        file->open(filename, std::ios::in);
        if (file->fail() || !file)
        {
            //TODO: log config file open failure
            //GameLogger::Current()->Log(LogType::FatalError, "Could not open configuration file [%s]. Aborting...\n", filename);
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
            key;
            //TODO: Log invalid-value configuration key error
            //GameLogger::Current()->Log(LogType::Error, "Found configuration key with an invalid value/no value: [%s]\n", key);
            return nullptr;
        }
        return buff;
    }
    bool ensureNothingElse(const char *&ptr, const char *const key, const char *const val)
    {
        auto err = Util::extractToken(ptr);
        if (err != nullptr)
        {
            key; val;
            //TODO: Log multi-value configuration key error
            //GameLogger::Current()->Log(LogType::Error, "Found configuration key with several values: [%s]. First value: [%s]\n", key, val);
        }
        return (err == nullptr);
    }

    bool closeFile(std::ifstream *file)
    {
        file->close();
        if (file->is_open())
        {
            //TODO: Log could-not-close-file error
            //GameLogger::Current()->Log(LogType::Error, "Could not close configuration file. Continuing...\n");
            return false;
        }
        return true;
    }
}
