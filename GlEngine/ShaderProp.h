#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED ShaderProp
        {
        public:
            ShaderProp(std::string name, bool isBuiltIn, int arrayLength = -1);
            ~ShaderProp();

            const std::string name;
            const bool isBuiltIn;
            const bool isArray;
            const int arrayLength;

            unsigned virtual LayoutSize() = 0;
            std::string virtual DeclarationString(std::string prefix = "") = 0;
        };
    }
}