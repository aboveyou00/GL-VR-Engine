#pragma once

namespace GlEngine::ShaderFactory
{
    FLAGS_H_DECL(PropertyFlag)
    {
        None     = 0b00000000,

        BuiltIn  = 0b00000001,
        Readonly = 0b00000010,
        Flat     = 0b00000100,
        Array    = 0b00001000
    };

    FLAGS_H(PropertyFlag)
}
