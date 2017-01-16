#include "stdafx.h"
#include "Snippet.h"
#include "Program.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Snippet::Snippet(std::string mainSource, PropertySourceFlag flags, std::string declSource)
            : PropertySource(flags), mainSource(mainSource), declSource(declSource)
        {
        }
        Snippet::Snippet(std::string mainSource, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> propertiesOut, PropertySourceFlag flags, std::string declSource)
            : PropertySource(flags), mainSource(mainSource), propertiesIn(propertiesIn), propertiesOut(propertiesOut), declSource(declSource)
        {
        }
        Snippet::~Snippet()
        {
        }
        Snippet * Snippet::IdentitySnippet(ShaderProp * prop, bool input, bool output)
        {
            if (!input && !output)
                assert(false);
            std::string format = (input && !output) ? "/* identity */ [out:0] = in_[in:0];" :
                                 (!input && output) ? "/* identity */ out_[out:0] = [in:0];" :
                                                      "/* identity */ out_[out:0] = in_[in:0];";
            return new Snippet(format, { prop }, { prop });
        }
        bool Snippet::HasProperty(ShaderProp* prop)
        {
            return std::find(propertiesOut.begin(), propertiesOut.end(), prop) != propertiesOut.end();
        }
        const std::vector<ShaderProp*> Snippet::inProperties()
        {
            return propertiesIn;
        }
        const std::vector<ShaderProp*> Snippet::outProperties()
        {
            return propertiesOut;
        }
        void Snippet::ProvideProperty(ShaderProp * prop, Program * program, ComponentType type)
        {
            prop;
            program;
            type;
        }
    }
}
