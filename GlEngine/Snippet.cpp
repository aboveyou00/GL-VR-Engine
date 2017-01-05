#include "stdafx.h"
#include "Snippet.h"

#include "StringUtils.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Snippet::Snippet(std::string source, bool fallback, std::string body)
            : source(source), fallback(fallback), body(body)
        {
        }
        Snippet::Snippet(std::string source, std::vector<Property*> propertiesIn, std::vector<Property*> propertiesOut, bool fallback, std::string body)
            : source(source), propertiesIn(propertiesIn), propertiesOut(propertiesOut), fallback(fallback), body(body)
        {
        }
        Snippet::~Snippet()
        {
        }
    }
}
