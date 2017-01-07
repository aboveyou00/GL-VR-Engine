#pragma once

namespace GlEngine
{
    namespace Events
    {
        enum class ENGINE_SHARED MouseEventType
        {
            Pressed,
            Released,
            Moved,
        };

        ENGINE_SHARED std::ostream &operator<<(std::ostream &stream, MouseEventType type);
    }
}
