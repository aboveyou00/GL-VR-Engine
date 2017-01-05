#include "stdafx.h"
#include "Snippet.h"
#include "Program.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Snippet::Snippet(std::string mainSource, bool fallback, std::string declSource)
            : mainSource(mainSource), fallback(fallback), declSource(declSource)
        {
        }
        Snippet::Snippet(std::string mainSource, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> propertiesOut, bool fallback, std::string declSource)
            : mainSource(mainSource), propertiesIn(propertiesIn), propertiesOut(propertiesOut), fallback(fallback), declSource(declSource)
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
