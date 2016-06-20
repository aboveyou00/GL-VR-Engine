#pragma once

namespace GlEngine
{
    namespace Events
    {
        enum class ENGINE_SHARED MouseButton : unsigned
        {
            None   = 0b00000,
            Left   = 0b00001,
            Right  = 0b00010,
            Middle = 0b00100,
            X1     = 0b01000,
            X2     = 0b10000
        };

        inline ENGINE_SHARED MouseButton operator|(MouseButton one, MouseButton two)
        {
            return static_cast<MouseButton>(static_cast<unsigned>(one) | static_cast<unsigned>(two));
        }
        inline ENGINE_SHARED MouseButton operator|=(MouseButton &one, MouseButton two)
        {
            return one = one | two;
        }
        inline ENGINE_SHARED MouseButton operator&(MouseButton one, MouseButton two)
        {
            return static_cast<MouseButton>(static_cast<unsigned>(one) & static_cast<unsigned>(two));
        }
        inline ENGINE_SHARED MouseButton operator&=(MouseButton &one, MouseButton two)
        {
            return one = one & two;
        }

        inline ENGINE_SHARED std::ostream &operator<<(std::ostream &stream, MouseButton btn)
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
