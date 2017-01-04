#include "stdafx.h"
#include "FactoryUtils.h"
#include "Snippet.h"
#include <regex>
#include <sstream>

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

            stream << &*lastEnd;
            return stream.str();
        }

        std::string resolveSnippetBody(Snippet *snippet)
        {
            auto source = regex_replace_label(snippet->source, R"raw(\[([^\]]*):(.*?)\])raw"s, [snippet](std::string type, std::string val) -> std::string {
                unsigned number;
                if (type == "in")
                {
                    (std::istringstream(val) >> number);
                    auto prop = snippet->localPropertiesIn[number];
                    if (prop->isBuiltIn) return prop->name;
                    else return "in_" + prop->name;
                }
                else if (type == "out")
                {
                    (std::istringstream(val) >> number);
                    auto prop = snippet->localPropertiesOut[number];
                    if (prop->isBuiltIn) return prop->name;
                    else return "out_" + prop->name;
                }
                else return "ERROR[" + type + ":" + val + "]";
            });
            return source;
        }
    }
}
