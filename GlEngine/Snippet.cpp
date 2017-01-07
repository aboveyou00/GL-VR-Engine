#include "stdafx.h"
#include "Snippet.h"
#include "Program.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Snippet::Snippet(std::string mainSource, SnippetFlag flags, std::string declSource)
            : mainSource(mainSource), flags(flags), declSource(declSource)
        {
        }
        Snippet::Snippet(std::string mainSource, std::vector<ShaderProp*> propertiesIn, std::vector<ShaderProp*> propertiesOut, SnippetFlag flags, std::string declSource)
            : mainSource(mainSource), propertiesIn(propertiesIn), propertiesOut(propertiesOut), flags(flags), declSource(declSource)
        {
        }
        Snippet::~Snippet()
        {
        }
        Snippet *Snippet::Copy()
        {
            std::vector<ShaderProp*> propertiesIn;
            std::vector<ShaderProp*> propertiesOut;
            std::vector<ShaderProp*> tempProperties;
            for (ShaderProp* prop : this->propertiesIn)
                propertiesIn.push_back(prop);
            for (ShaderProp* prop : this->propertiesOut)
                propertiesOut.push_back(prop);
            for (ShaderProp* prop : this->tempProperties)
                tempProperties.push_back(prop);
            auto snippet = new Snippet(mainSource, propertiesIn, propertiesOut, flags, declSource);
            snippet->tempProperties = tempProperties;
            return snippet;
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
        void Snippet::ProvideProperty(ShaderProp * prop, Program * program, ComponentType type)
        {
            prop;
            program;
            type;
        }

        bool Snippet::HasFlag(SnippetFlag flag) const
        {
            return (flags & flag) != SnippetFlag::None;
        }
        void Snippet::SetFlag(SnippetFlag flag, bool val)
        {
            if (val) flags |= flag;
            else flags &= ~flag;
        }
        void Snippet::SetFlag(SnippetFlag flag)
        {
            SetFlag(flag, true);
        }
        void Snippet::ResetFlag(SnippetFlag flag)
        {
            SetFlag(flag, false);
        }

        bool Snippet::fallback() const
        {
            return HasFlag(SnippetFlag::Fallback);
        }
        bool Snippet::noSideEffects() const
        {
            return HasFlag(SnippetFlag::NoSideEffects);
        }
        bool Snippet::hasSideEffects() const
        {
            return !HasFlag(SnippetFlag::NoSideEffects);
        }
    }
}
