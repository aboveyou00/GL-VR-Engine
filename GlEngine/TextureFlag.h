#pragma once

namespace GlEngine
{
    FLAGS_H_PREDECL(TextureFlag)

    FLAGS_H_DECL(TextureFlag)
    {
        None         = 0,
        Translucent  = 0b00001,
        AlphaMap     = 0b00010,
        NormalMask   = 0b00100,
        RenderTarget = 0b01000,
        Clamp        = 0b10000
    };

    FLAGS_H(TextureFlag)
}
