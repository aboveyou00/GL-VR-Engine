#pragma once

namespace GlEngine
{
    namespace Events
    {
        enum class MouseEventType
        {
            Pressed,
            Released,
            Moved,
        };

        inline std::ostream &operator<<(std::ostream &stream, MouseEventType type)
        {
            switch (type)
            {
            case GlEngine::Events::MouseEventType::Pressed:
                return stream << "Mouse Button Pressed";
            case GlEngine::Events::MouseEventType::Released:
                return stream << "Mouse Button Released";
            case GlEngine::Events::MouseEventType::Moved:
                return stream << "Mouse Moved";
            default:
                return stream << "ERROR(MouseEventType)";
            }
        }
    }
}
