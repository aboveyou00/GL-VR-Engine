#pragma once

namespace GlEngine
{
    namespace Util
    {
        //IMPORTANT: Each time you call this method, the strings returned by previous calls are invalidated.
        //If inputs are invalid, nullptr is returned
        ENGINE_SHARED const char *const createLogFileName(const char *const path, const char *const filename);
        ENGINE_SHARED bool createLogFileName(char *buff, int buffSize, const char *const path, const char *const filename);

        ENGINE_SHARED const char *const combinePath(const char *const path, const char *const filename);
        ENGINE_SHARED bool combinePath(char *buff, int buffSize, const char *const path, const char *const filename);
    }
}
