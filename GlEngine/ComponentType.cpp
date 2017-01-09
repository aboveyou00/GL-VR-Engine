#include "stdafx.h"
#include "ComponentType.h"
#include "ComponentType_attribs.h"

namespace GlEngine::ShaderFactory
{
    ENGINE_SHARED std::ostream &operator<<(std::ostream &stream, ComponentType type)
    {
        return stream << NameOf(type);
    }
}

CONTIGUOUS_ENUM_CPP(GlEngine::ShaderFactory::ComponentType)
