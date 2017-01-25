#include "stdafx.h"
#include "FactoryUtils.h"
#include "StringUtils.h"
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
        std::string resolveSnippetBody(Snippet* snippet, int tabulation, std::string main)
        {
            if (main == "")
                main = snippet->mainSource;

            auto tabulationStr = std::string(tabulation, ' ');

            auto source = Util::regex_replace_callback(main, R"raw(\[([a-z]*):(.*?)\])raw"s, [snippet](std::smatch match) -> std::string {
                std::string type = match[1],
                            val = match[2];

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
