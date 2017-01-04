#pragma once

namespace GlEngine
{
    namespace Util
    {
        ENGINE_SHARED long long getGameMillis() noexcept;
        //IMPORTANT: Each time you call this method, the strings returned by previous calls are invalidated.
        ENGINE_SHARED const char *const getTimestamp() noexcept;
        ENGINE_SHARED bool getTimestamp(char *buff, int buffSize) noexcept;
    }
}
