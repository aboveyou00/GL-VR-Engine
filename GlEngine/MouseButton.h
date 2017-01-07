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

        ENGINE_SHARED MouseButton operator|(MouseButton one, MouseButton two);
        ENGINE_SHARED MouseButton operator|=(MouseButton &one, MouseButton two);
        ENGINE_SHARED MouseButton operator&(MouseButton one, MouseButton two);
        ENGINE_SHARED MouseButton operator&=(MouseButton &one, MouseButton two);

        ENGINE_SHARED std::ostream &operator<<(std::ostream &stream, MouseButton btn);
    }
}
