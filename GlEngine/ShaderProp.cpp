#include "stdafx.h"
#include "ShaderProp.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        ShaderProp::ShaderProp(std::string name, PropertyFlag flags)
            : name(name), flags(flags)
        {
        }
        ShaderProp::~ShaderProp()
        {
        }

        bool ShaderProp::hasFlag(PropertyFlag flag) const
        {
            return (flags & flag) != PropertyFlag::None;
        }
        void ShaderProp::SetFlag(PropertyFlag flag, bool val)
        {
            if (val) flags |= flag;
            else flags &= ~flag;
        }
        void ShaderProp::SetFlag(PropertyFlag flag)
        {
            SetFlag(flag, true);
        }
        void ShaderProp::ResetFlag(PropertyFlag flag)
        {
            SetFlag(flag, false);
        }

        bool ShaderProp::isBuiltIn() const
        {
            return hasFlag(PropertyFlag::BuiltIn);
        }
        bool ShaderProp::isReadonly() const
        {
            return hasFlag(PropertyFlag::Readonly);
        }
        bool ShaderProp::isFlat() const
        {
            return hasFlag(PropertyFlag::Flat);
        }
        bool ShaderProp::isArray() const
        {
            return hasFlag(PropertyFlag::Array);
        }

        std::string ShaderProp::modifier()
        {
            if (isFlat()) return "flat"s;
            else return ""s;
        }
    }
}
