#include "stdafx.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Snippet::Snippet(std::string source, bool fallback, std::string body)
            : source(source), fallback(fallback), body(body)
        {
        }
        Snippet::Snippet(std::string source, std::vector<ShaderProp*> localPropertiesIn, std::vector<ShaderProp*> localPropertiesOut, bool fallback, std::string body)
            : source(source), localPropertiesIn(localPropertiesIn), localPropertiesOut(localPropertiesOut), fallback(fallback), body(body)
        {
        }
        Snippet::~Snippet()
        {
        }
    }
}
