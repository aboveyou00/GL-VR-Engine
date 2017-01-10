#pragma once

namespace GlEngine::ShaderFactory
{
    class ShaderFactory;
    class ShaderProp;

    class ENGINE_SHARED IPropertyProvider
    {
    public:
        virtual std::vector<ShaderProp*> properties() = 0;

        virtual void Push(ShaderFactory &factory) = 0;
    };
}
