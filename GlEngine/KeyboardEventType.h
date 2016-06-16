#pragma once

namespace GlEngine
{
    namespace Events
    {
        enum class KeyboardEventType
        {
            KeyPressed = 0,
            KeyReleased = 1,
            KeyTyped = 2
        };

        inline std::ostream &operator<<(std::ostream &stream, KeyboardEventType type)
        {
            switch (type)
            {
            case GlEngine::Events::KeyboardEventType::KeyPressed:
                return stream << "Key Pressed";
            case GlEngine::Events::KeyboardEventType::KeyReleased:
                return stream << "Key Released";
            case GlEngine::Events::KeyboardEventType::KeyTyped:
                return stream << "Key Typed";
            default:
                return stream << "ERROR(KeyboardEventType)";
            }
        }
    }
}
