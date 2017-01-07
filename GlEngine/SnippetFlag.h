#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        FLAGS_H_DECL(SnippetFlag)
        {
            None          = 0b00000000,
            Fallback      = 0b00000001,
            NoSideEffects = 0b00000010
        };

        FLAGS_H(SnippetFlag)
    }
}
