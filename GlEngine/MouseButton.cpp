#include "stdafx.h"
#include "MouseButton.h"

namespace GlEngine
{
    namespace Events
    {
        MouseButton operator|(MouseButton one, MouseButton two)
        {
            return static_cast<MouseButton>(static_cast<unsigned>(one) | static_cast<unsigned>(two));
        }
        MouseButton operator|=(MouseButton &one, MouseButton two)
        {
            return one = one | two;
        }
        MouseButton operator&(MouseButton one, MouseButton two)
        {
            return static_cast<MouseButton>(static_cast<unsigned>(one) & static_cast<unsigned>(two));
        }
        MouseButton operator&=(MouseButton &one, MouseButton two)
        {
            return one = one & two;
        }

        std::ostream &operator<<(std::ostream &stream, MouseButton btn)
        {
            switch (btn)
            {
            case GlEngine::Events::MouseButton::None:
                return stream << "None";
            case GlEngine::Events::MouseButton::Left:
                return stream << "Left";
            case GlEngine::Events::MouseButton::Right:
                return stream << "Right";
            case GlEngine::Events::MouseButton::Middle:
                return stream << "Middle";
            case GlEngine::Events::MouseButton::X1:
                return stream << "X1";
            case GlEngine::Events::MouseButton::X2:
                return stream << "X2";
            default:
                return stream << "ERROR(MouseButton)";
            }
        }
    }
}
