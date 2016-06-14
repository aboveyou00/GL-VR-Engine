#pragma once

namespace GlEngine
{
    namespace Events
    {
        enum class MouseButton : unsigned
        {
            None   = 0b00000,
            Left   = 0b00001,
            Right  = 0b00010,
            Middle = 0b00100,
            X1     = 0b01000,
            X2     = 0b10000
        };

        inline MouseButton operator|(MouseButton one, MouseButton two)
        {
            return static_cast<MouseButton>(static_cast<unsigned>(one) | static_cast<unsigned>(two));
        }
        inline MouseButton operator|=(MouseButton &one, MouseButton two)
        {
            return one = one | two;
        }
        inline MouseButton operator&(MouseButton one, MouseButton two)
        {
            return static_cast<MouseButton>(static_cast<unsigned>(one) & static_cast<unsigned>(two));
        }
        inline MouseButton operator&=(MouseButton &one, MouseButton two)
        {
            return one = one & two;
        }

        inline std::ostream &operator<<(std::ostream &stream, MouseButton btn)
        {
            btn;
            return stream << "TODO(Impl operator<<(ostream, MouseButton))";
        }
    }
}
