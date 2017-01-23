#include "stdafx.h"
#include "Snippet.h"
#include "Program.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Snippet::Snippet(std::string mainSource, PropertySourceFlag flags, std::vector<ComponentType> supportedComponents, std::string declSource)
            : PropertySource(flags, supportedComponents), mainSource(mainSource), declSource(declSource)
        {
        }
        Snippet::Snippet(std::string mainSource, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> propertiesOut, PropertySourceFlag flags, std::vector<ComponentType>supportedComponents, std::string declSource)
            : PropertySource(flags, supportedComponents), mainSource(mainSource), propertiesIn(propertiesIn), propertiesOut(propertiesOut), declSource(declSource)
        {
        }
        Snippet::~Snippet()
        {
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

        const std::vector<ShaderProp*> Snippet::inProperties()
        {
            return propertiesIn;
        }

        const std::vector<ShaderProp*> Snippet::outProperties()
        {
            return propertiesOut;
        }
        void Snippet::Inject(Program * program, ComponentType type)
        {
            for (size_t i = 0; i < propertiesIn.size(); i++)
            {
                if (program->components[type]->allProps.find(propertiesIn[i]) == program->components[type]->allProps.end())
                {
                    ComponentType inputType = program->sourceComponents[program->propertySourceInputs[this][i]];
                    program->propertySourceInputs[this][i]->ProvideInput(program, propertiesIn[i], inputType, type);
                }
            }
            program->components[type]->AddSnippet(this);
        }
    }
}
