#pragma once

#include "PropertyFlag.h"

namespace GlEngine::ShaderFactory
{
    class ENGINE_SHARED ShaderProp
    {
    public:
        ShaderProp(std::string name, PropertyFlag flags = PropertyFlag::None);
        ~ShaderProp();

        const std::string name;

        bool hasFlag(PropertyFlag flag) const;
        void SetFlag(PropertyFlag flag, bool val);
        void SetFlag(PropertyFlag flag);
        void ResetFlag(PropertyFlag flag);

        bool isBuiltIn() const;
        bool isReadonly() const;
        bool isFlat() const;
        bool isArray() const;

        unsigned virtual layoutSize() = 0;
        std::string virtual DeclarationString(std::string prefix = ""s) = 0;
        std::string virtual modifier();

    private:
        PropertyFlag flags;
    };
}
