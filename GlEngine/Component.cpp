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
            : type(type), ins({}), outs({}), unresolvedInputs({}), availableLocalProps({}), unresolvedOutputs({}), unresolvedSnippets({}), comments("")
        {
        }
        Component::~Component()
        {
        }

        bool Component::ResolveSnippets()
        {
            for (auto it: ins)
                addLocalProp(it.second);
            for (auto it : uniforms)
                addLocalProp(it.second);

            unsigned last_size = 0;
            bool changed = false;
            while (unresolvedSnippets.size() > 0)
            {
                if (unresolvedSnippets.size() == last_size)
                    break;
                last_size = unresolvedSnippets.size();

                std::vector<Snippet*> resolved;
                for (Snippet* snippet : unresolvedSnippets)
                {
                    if (snippetDependenciesMet(snippet))
                    {
                        orderedSnippets.push_back(snippet);
                        resolved.push_back(snippet);
                        for (ShaderProp* prop : snippet->propertiesOut)
                            addLocalProp(prop);
                        changed = true;
                    }
                }
                for (Snippet* snippet : resolved)
                    unresolvedSnippets.erase(snippet);
            }
            unresolvedOutputs.clear();
            unresolvedInputs.clear();
            for (Snippet* snippet : unresolvedSnippets)
            {
                for (size_t q = 0; q < snippet->propertiesIn.size(); q++)
                    if (std::find(availableLocalProps.begin(), availableLocalProps.end(), snippet->propertiesIn[q]) == availableLocalProps.end())
                        unresolvedInputs.insert(snippet->propertiesIn[q]);
                for (size_t q = 0; q < snippet->propertiesOut.size(); q++)
                    unresolvedOutputs.insert(snippet->propertiesOut[q]);
            }
            return changed;
        }
        bool Component::IsResolved()
        {
            return unresolvedSnippets.size() == 0;
        }

        bool Component::snippetDependenciesMet(Snippet* snippet)
        {
            for (ShaderProp* prop : snippet->propertiesIn)
                if (std::find(availableLocalProps.begin(), availableLocalProps.end(), prop) == availableLocalProps.end())
                    return false;
            return true;
        }
        void Component::addLocalProp(ShaderProp *prop)
        {
            if (std::find(availableLocalProps.begin(), availableLocalProps.end(), prop) == availableLocalProps.end())
                availableLocalProps.insert(prop);
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
                    stream << "layout(location = " << it.first << ") uniform " << it.second->DeclarationString("in_") << ";" << std::endl;
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
            for (Snippet* snippet : orderedSnippets)
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
            for (ShaderProp* prop : availableLocalProps)
            {
                if (prop->isBuiltIn) continue;
                stream << tabulationString << prop->DeclarationString() + ";" << std::endl;
                any = true;
            }
            for (size_t q = 0; q < orderedSnippets.size(); q++)
            {
                auto snippet = orderedSnippets[q];
                for (ShaderProp* prop : snippet->tempProperties)
                {
                    stream << tabulationString << prop->DeclarationString() + ";" << std::endl;
                    any = true;
                }
            }
            if (any) stream << tabulationString << std::endl;
        }

        void Component::compileMain(std::stringstream &stream, int tabulation)
        {            
            for (Snippet* snippet : orderedSnippets)
                stream << resolveSnippetBody(snippet, tabulation) << std::endl;
        }
    }
}
