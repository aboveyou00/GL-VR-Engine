#include "stdafx.h"
#include "FactoryUtils.h"
#include "Program.h"
#include "Snippet.h"
#include "Property.h"
#include <regex>
#include <sstream>
#include <iostream>

namespace GlEngine
{
    namespace ShaderFactory
    {
        std::string regex_replace_label(std::string source, std::string regex, std::function<std::string(std::string, std::string)> func)
        {
            std::regex r(regex);

            std::string::const_iterator lastEnd(source.cbegin());

            std::stringstream stream;
            while (true) {
                std::smatch results;
                if (!std::regex_search(lastEnd, source.cend(), results, r)) break;

                stream << std::string(&*lastEnd, &*lastEnd + results.position());
                stream << func(results[1], results[2]);

                lastEnd += results.position() + results.length();
            }

            if (lastEnd != source.cend())
                stream << &*lastEnd;
            return stream.str();
        }

        std::string resolveSnippetBody(Snippet *snippet, int tabulation)
        {
            std::string tabulationStr;
            for (int q = 0; q < tabulation; q++)
                tabulationStr += " ";

            auto source = regex_replace_label(snippet->mainSource, R"raw(\[([^\]]*):(.*?)\])raw"s, [snippet](std::string type, std::string val) -> std::string {
                auto vec = type == "in" ? &snippet->propertiesIn :
                          type == "out" ? &snippet->propertiesOut :
                         type == "temp" ? &snippet->tempProperties :
                                          nullptr;
                unsigned number;
                (std::istringstream(val) >> number);
                if (vec == nullptr || number >= vec->size()) return "ERROR[" + type + ":" + val + "]";
                auto prop = (*vec)[number];
                //TODO: get property source from program and return the name from that, if possible (important for constant values)
                return prop->name;
            });
            static std::regex newlineRegex(R"raw(\r?\n)raw"s);
            return tabulationStr + std::regex_replace(source, newlineRegex, "\n"s + tabulationStr);
        }
    }
}
