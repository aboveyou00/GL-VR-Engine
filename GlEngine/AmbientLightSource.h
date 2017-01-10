#pragma once

#include "IPropertyProvider.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ShaderProp;
        class ShaderFactory;
    }

    class ENGINE_SHARED AmbientLightSource : public ShaderFactory::IPropertyProvider
    {
    public:
        AmbientLightSource(Vector<3> color);
        ~AmbientLightSource();

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;

        virtual void Push(ShaderFactory::ShaderFactory &factory) override;

        Vector<3> color();
        void SetColor(Vector<3> color);

    private:
        Vector<3> _color;
    };
}
