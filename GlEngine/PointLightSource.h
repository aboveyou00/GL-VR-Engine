#pragma once

#include "IPropertyProvider.h"

namespace GlEngine
{
    class ENGINE_SHARED PointLightSource : public ShaderFactory::IPropertyProvider
    {
    public:
        PointLightSource(Vector<3> pos = {}, Vector<3> diffuseColor = { 1, 1, 1 }, Vector<3> specularColor = { 1, 1, 1 }, bool attenuation = false);
        ~PointLightSource();

        virtual void Push(ShaderFactory::ShaderFactory &factory) override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;

        Vector<3> position();
        void SetPosition(Vector<3> pos);

        Vector<3> diffuseColor();
        void SetDiffuseColor(Vector<3> color);

        Vector<3> specularColor();
        void SetSpecularColor(Vector<3> color);

        bool attenuation();
        void SetAttenuation(bool val);

    private:
        Vector<3> _pos, _diffuseColor, _specularColor;
        bool _attenuation;
    };
}
