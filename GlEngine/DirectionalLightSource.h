#pragma once

#include "IPropertyProvider.h"

namespace GlEngine
{
    class DirectionalLightSource : public ShaderFactory::IPropertyProvider
    {
    public:
        DirectionalLightSource(Vector<3> direction, Vector<3> color);
        ~DirectionalLightSource();

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;

        virtual void Push(ShaderFactory::ShaderFactory &factory) override;

        Vector<3> direction();
        void SetDirection(Vector<3> direction);

        Vector<3> color();
        void SetColor(Vector<3> color);

    private:
        Vector<3> _direction, _color;
    };
}
