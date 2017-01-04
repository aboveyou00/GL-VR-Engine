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
            Snippet(std::string source, std::vector<Property*> localPropertiesIn = std::vector<Property*>(), std::vector<Property*> localPropertiesOut = std::vector<Property*>());
            ~Snippet();

            std::string source;
            std::vector<Property*> localPropertiesIn;
            std::vector<Property*> localPropertiesOut;
        };
    }
}