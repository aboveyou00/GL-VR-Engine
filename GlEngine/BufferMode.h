#pragma once

namespace GlEngine
{
    enum class BufferMode : unsigned
    {
        Array = 0x8892,
        ElementArray = 0x8893,

        CopyRead = 0x8F36,
        CopyWrite = 0x8F37,
        DrawIndirect = 0x8F3F,
        PixelPack = 0x88EB,
        PixelUnpack = 0x88EC,
        Texture = 0x8C2A,
        TransformFeedback = 0x8C8E,
        Uniform = 0x8A11
    };
}
