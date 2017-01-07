#pragma once

namespace GlEngine
{
    namespace Events
    {
        enum class ENGINE_SHARED KeyboardEventType
        {
            KeyPressed = 0,
            KeyReleased = 1,
            KeyTyped = 2
        };

        ENGINE_SHARED std::ostream &operator<<(std::ostream &stream, KeyboardEventType type);
    }
}
