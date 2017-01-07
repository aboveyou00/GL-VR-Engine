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
        Snippet * Snippet::Copy()
        {
            std::vector<ShaderProp*> propertiesIn;
            std::vector<ShaderProp*> propertiesOut;
            for (ShaderProp* prop : this->propertiesIn)
                propertiesIn.push_back(prop);
            for (ShaderProp* prop : this->propertiesOut)
                propertiesOut.push_back(prop);
            return new Snippet(mainSource, propertiesIn, propertiesOut, fallback, declSource);
        }
        Snippet * Snippet::IdentitySnippet(ShaderProp * prop, bool input, bool output)
        {
            if (!input && !output)
                assert(false);
            std::string format = (input && !output) ? "[out:0] = in_[in:0];" :
                                 (!input && output) ? "out_[out:0] = [in:0];" :
                                                      "out_[out:0] = in_[in:0];";
            return new Snippet(format, { prop }, { prop });
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
