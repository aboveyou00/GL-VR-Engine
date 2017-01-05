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
<<<<<<< HEAD
            Snippet(std::string source, std::vector<Property*> propertiesIn, std::vector<Property*> proportiesOut, bool fallback = false, std::string body = ""s);
            ~Snippet();

            std::string source, body;
            std::vector<Property*> propertiesIn;
            std::vector<Property*> propertiesOut;
=======
            Snippet(std::string source, std::vector<ShaderProp*> localPropertiesIn, std::vector<ShaderProp*> localPropertiesOut, bool fallback = false, std::string body = ""s);
            ~Snippet();

            std::string source, body;
            std::vector<ShaderProp*> localPropertiesIn;
            std::vector<ShaderProp*> localPropertiesOut;
>>>>>>> 9a332fad24e8f2e4cf0df4e95d7ead07270d041e
            bool fallback;

			static Snippet* IdentitySnippet(Property* prop)
			{
				return new Snippet("[OUT:0] = [IN:0]", {prop}, {prop});
			}
        };
    }
}
