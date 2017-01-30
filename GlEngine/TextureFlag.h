#pragma once

namespace GlEngine
{
    FLAGS_H_PREDECL(TextureFlag)

    FLAGS_H_DECL(TextureFlag)
    {
        None         = 0,
        Translucent  = 0b0001,
        AlphaMap     = 0b0010,
        RenderTarget = 0b0100
    };

    FLAGS_H(TextureFlag)
}
