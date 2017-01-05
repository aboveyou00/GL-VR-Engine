#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Snippet;
        class ShaderProp;

        std::string PropertyName(ShaderProp* prop, bool in);
        std::string resolveSnippetBody(Snippet *snippet);
    }
}
