#include "stdafx.h"
#include "Component.h"
#include "ComponentType_attribs.h"

#include "StringUtils.h"
#include "LogUtils.h"

#include "Snippet.h"
#include "FactoryUtils.h"
#include <regex>

namespace GlEngine
{
    namespace ShaderFactory
    {
        Component::Component(ComponentType type)
            : type(type), ins({}), outs({}), comments("")
        {
        }
        Component::~Component()
        {
        }

        unsigned Component::FindOrCreateOutput(ShaderProp * prop)
        {
            for (auto it : outs)
                if (it.second == prop)
                    return it.first;
            unsigned idx = outs.size();
            outs[idx] = prop;
            return idx;
        }

        std::string Component::Compile()
        {
            std::stringstream stream;

            compileVersion(stream);
            compileLayouts(stream);
            compileDecl(stream);

            stream << "void main(void) {" << std::endl;

            compilePropertyDeclarations(stream, 4);

            compileMain(stream, 4);
            stream << "\n" << comments;
            stream << "}" << std::endl;

            compiled = stream.str();
            //int linen = 1;
            //compiled = "/* 1 */ " + Util::regex_replace_callback(compiled, R"raw(\r?\n)raw"s, [&](std::smatch match) -> std::string {
            //    return "\n/* " + Util::itos(++linen) + " */ ";
            //});
            return compiled;
        }

        void Component::AddIdentitySnippet(ShaderProp* prop, bool input, bool output)
        {
            if (output)
                outputSnippets.push_back(Snippet::IdentitySnippet(prop, input, output));
            else
                inputSnippets.push_back(Snippet::IdentitySnippet(prop, input, output));
            allProps.insert(prop);
        }

        void Component::AddSnippet(Snippet* snippet)
        {
            snippets.push_back(snippet);
            for (auto prop : snippet->inProperties())
                allProps.insert(prop);
            for (auto prop : snippet->outProperties())
                allProps.insert(prop);
        }

        void Component::AddUnresolvedSnippet(Snippet* snippet, int tabulation)
        {
            static std::regex newlineRegex(R"raw(\r?\n)raw"s);
            std::string commented = "//" + std::regex_replace(snippet->mainSource, newlineRegex, "\n//"s);
            commented = "// ********** UNRESOLVED SNIPPET **********\n"s + commented + "\n// *******************************"s;
            comments += resolveSnippetBody(snippet, tabulation, commented) + "\n";
        }

        void Component::compileVersion(std::stringstream &stream)
        {
            stream << "#version 430" << std::endl << std::endl;
        }

        void Component::compileLayouts(std::stringstream &stream)
        {
            std::string result = "";

            if (uniforms.size() > 0)
            {
                for (auto it : uniforms)
                {
                    stream << "layout(location = " << it.first << ") uniform ";
                    stream << it.second->DeclarationString(it.second->isReadonly() ? ""s : "in_"s);
                    stream << ";" << std::endl;
                }
                stream << std::endl;
            }
            if (ins.size() > 0)
            {
                for (auto it : ins)
                {
                    std::string modifier = "";
                    if (type == ComponentType::Fragment || type == ComponentType::TessControl || type == ComponentType::Geometry)
                        modifier = it.second->modifier();
                    if (modifier.size() > 0)
                        modifier += " ";
                    stream << "layout(location = " << it.first << ") " << modifier << "in " << it.second->DeclarationString("in_") << ";" << std::endl;
                }
                stream << std::endl;
            }
            if (outs.size() > 0)
            {
                for (auto it : outs)
                {
                    std::string modifier = "";
                    if (type == ComponentType::Vertex || type == ComponentType::TessEvaluation || type == ComponentType::Geometry)
                        modifier = it.second->modifier();
                    if (modifier.size() > 0)
                        modifier += " ";
                    stream << "layout(location = " << it.first << ") " << modifier << "out " << it.second->DeclarationString("out_") << ";" << std::endl;
                }
                stream << std::endl;
            }
        }

        void Component::compileDecl(std::stringstream &stream)
        {
            std::string result = "";
            bool any = false;
            for (Snippet* snippet : snippets)
            {
                if (!Util::is_empty_or_ws(snippet->declSource.c_str()))
                {
                    stream << snippet->declSource << std::endl;
                    any = true;
                }
            }
            if (any) stream << std::endl;
        }

        void Component::compilePropertyDeclarations(std::stringstream &stream, int tabulation)
        {
            auto tabulationString = std::string(tabulation, ' ');

            bool any = false;
            for (ShaderProp* prop : allProps)
            {
                if (prop->isBuiltIn() || prop->isReadonly())
                    continue;
                stream << tabulationString << prop->DeclarationString() + ";" << std::endl;
                any = true;
            }
            if (any)
            {
                stream << tabulationString << std::endl;
                any = false;
            }
            
            for (size_t q = 0; q < snippets.size(); q++)
            {
                auto snippet = snippets[q];
                for (ShaderProp* prop : snippet->tempProperties)
                {
                    stream << tabulationString << prop->DeclarationString() + ";" << std::endl;
                    any = true;
                }
            }
            if (any)
            {
                stream << tabulationString << std::endl;
                any = false;
            }
        }

        void Component::compileMain(std::stringstream &stream, int tabulation)
        {            
            stream << "/* BEGIN INPUT IDENTITIES */ " << std::endl;
            for (Snippet* snippet : inputSnippets)
                stream << resolveSnippetBody(snippet, tabulation) << std::endl;
            stream << "/* END INPUT IDENTITIES */ " << std::endl << std::endl;

            for (Snippet* snippet : snippets)
                stream << resolveSnippetBody(snippet, tabulation) << std::endl;

            stream << std::endl << "/* BEGIN OUTPUT IDENTITIES */" << std::endl;
            for (Snippet* snippet : outputSnippets)
                stream << resolveSnippetBody(snippet, tabulation) << std::endl;
            stream << "/* END OUTPUT IDENTITIES */" << std::endl;
        }
    }
}
