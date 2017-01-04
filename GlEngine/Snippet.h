#pragma once
#include "Property.h"
#include "Component.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Snippet
        {
        public:
            Snippet(std::string source, bool fallback = false, std::string body = ""s);
            Snippet(std::string source, std::vector<Property*> localPropertiesIn, std::vector<Property*> localPropertiesOut, bool fallback = false, std::string body = ""s);
            ~Snippet();

            std::string source, body;
            std::vector<Property*> localPropertiesIn;
            std::vector<Property*> localPropertiesOut;
            bool fallback;
        };
    }
}
