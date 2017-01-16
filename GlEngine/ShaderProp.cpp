#include "stdafx.h"
#include "ShaderProp.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        ShaderProp::ShaderProp(std::string name, bool isBuiltIn, bool isFlat, int arrayLength)
            : name(name), isBuiltIn(isBuiltIn), arrayLength(arrayLength), isFlat(isFlat), isArray(arrayLength >= 0)
        {
        }
        ShaderProp::~ShaderProp()
        {
        }

        std::string ShaderProp::modifier()
        {
            if (isFlat)
                return "flat";
            else
                return "";
        }
    }
}
