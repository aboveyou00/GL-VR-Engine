#include "stdafx.h"
#include "Snippet.h"
#include "Program.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Snippet::Snippet(std::string source, bool fallback, std::string body)
            : source(source), fallback(fallback), body(body)
        {
        }
        Snippet::Snippet(std::string source, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> propertiesOut, bool fallback, std::string body)
            : source(source), propertiesIn(propertiesIn), propertiesOut(propertiesOut), fallback(fallback), body(body)
        {
        }
        Snippet::~Snippet()
        {
        }
        bool Snippet::HasProperty(ShaderProp* prop)
        {
            return std::find(propertiesOut.begin(), propertiesOut.end(), prop) != propertiesOut.end();
        }
        void Snippet::ProvideProperty(ShaderProp * prop, Program * program, ComponentType type)
        {
            prop;
            program;
            type;
        }
    }
}
