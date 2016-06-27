#include "stdafx.h"
#include "PathUtils.h"
#include "TimeUtils.h"

namespace GlEngine
{
    namespace Util
    {
        //IMPORTANT: Each time you call this method, the strings returned by previous calls are invalidated.
        //If inputs are invalid, nullptr is returned
        const char *const createLogFileName(const char *const path, const char *const filename)
        {
            static thread_local char buff[256];
            if (!createLogFileName(buff, sizeof(buff), path, filename)) return nullptr;
            return buff;
        }
        bool createLogFileName(char *buff, int buffSize, const char *const path, const char *const filename)
        {
            bool appendSlash = false;
            auto len = (path == nullptr ? 0 : strnlen_s(path, 128));
            if (len > 0 && *(path + len - 1) != '\\') appendSlash = true;

            return sprintf_s(buff, buffSize, "%s%s%s.%s", path, (appendSlash ? "\\" : ""), getTimestamp(), filename) > 0;
        }

        const char *const combinePath(const char *const path, const char *const filename)
        {
            static thread_local char buff[256];
            if (!combinePath(buff, sizeof(buff), path, filename)) return nullptr;
            return buff;
        }
        bool combinePath(char *buff, int buffSize, const char *const path, const char *const filename)
        {
            bool appendSlash = false;
            auto len = (path == nullptr ? 0 : strnlen_s(path, 128));
            if (len > 0 && *(path + len - 1) != '\\') appendSlash = true;

            return sprintf_s(buff, buffSize, "%s%s%s", path, (appendSlash ? "\\" : ""), filename) > 0;
        }
    }
}
