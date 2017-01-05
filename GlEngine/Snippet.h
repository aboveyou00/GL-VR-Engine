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
            Snippet(std::string source, std::vector<Property*> propertiesIn, std::vector<Property*> proportiesOut, bool fallback = false, std::string body = ""s);
            ~Snippet();

            std::string source, body;
            std::vector<Property*> propertiesIn;
            std::vector<Property*> propertiesOut;
            bool fallback;

			static Snippet* IdentitySnippet(Property* prop)
			{
				return new Snippet("[OUT:0] = [IN:0]", {prop}, {prop});
			}
        };
    }
}
