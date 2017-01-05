#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Property;

        class ENGINE_SHARED Snippet
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
