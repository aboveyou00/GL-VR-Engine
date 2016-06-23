#pragma once

namespace GlEngine
{
    namespace Util
    {
        //IMPORTANT: Each time you call this method, the strings returned by previous calls are invalidated.
        ENGINE_SHARED const char *const getTimestamp();
        ENGINE_SHARED bool getTimestamp(char *buff, int buffSize);
    }
}
