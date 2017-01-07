#include "stdafx.h"
#include "KeyboardEventType.h"

namespace GlEngine
{
    namespace Events
    {
        std::ostream &operator<<(std::ostream &stream, KeyboardEventType type)
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
