#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ShaderProp;

        class ENGINE_SHARED Snippet
        {
        public:
            Snippet(std::string source, bool fallback = false, std::string body = ""s);
            Snippet(std::string source, std::vector<ShaderProp*> localPropertiesIn, std::vector<ShaderProp*> localPropertiesOut, bool fallback = false, std::string body = ""s);
            ~Snippet();

            std::string source, body;
            std::vector<ShaderProp*> localPropertiesIn;
            std::vector<ShaderProp*> localPropertiesOut;
            bool fallback;
        };
    }
}
