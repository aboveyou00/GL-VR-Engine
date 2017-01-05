#include "stdafx.h"
#include "ShaderProp.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        ShaderProp::ShaderProp(std::string name, bool isBuiltIn, int arrayLength)
            : name(name), isBuiltIn(isBuiltIn), arrayLength(arrayLength), isArray(arrayLength >= 0)
        {
        }
        ShaderProp::~ShaderProp()
        {
        }
    }
}
