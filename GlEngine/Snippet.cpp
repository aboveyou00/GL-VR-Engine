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
<<<<<<< HEAD
        Snippet::Snippet(std::string source, std::vector<Property*> propertiesIn, std::vector<Property*> propertiesOut, bool fallback, std::string body)
            : source(source), propertiesIn(propertiesIn), propertiesOut(propertiesOut), fallback(fallback), body(body)
=======
        Snippet::Snippet(std::string source, std::vector<ShaderProp*> localPropertiesIn, std::vector<ShaderProp*> localPropertiesOut, bool fallback, std::string body)
            : source(source), localPropertiesIn(localPropertiesIn), localPropertiesOut(localPropertiesOut), fallback(fallback), body(body)
>>>>>>> 9a332fad24e8f2e4cf0df4e95d7ead07270d041e
        {
        }
        Snippet::~Snippet()
        {
        }
    }
}
