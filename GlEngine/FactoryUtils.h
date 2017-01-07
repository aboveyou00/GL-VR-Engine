#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Program;
        class Snippet;
        class ShaderProp;

        std::string resolveSnippetBody(Snippet *snippet, int tabulation = 0);
    }
}
