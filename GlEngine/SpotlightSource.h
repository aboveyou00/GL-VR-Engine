#pragma once

#include "IPropertyProvider.h"
#include "MathUtils.h"

namespace GlEngine
{
    class SpotlightSource : public ShaderFactory::IPropertyProvider
    {
    public:
        SpotlightSource(Vector<3> position, Vector<3> color, float angleAttenuation = .5f, Vector<3> direction = { 0, 0, 0 }, float cutoffTheta = 45deg);
        ~SpotlightSource();

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;

        virtual void Push(ShaderFactory::ShaderFactory &factory) override;

        void SetPosition(Vector<3> position);
        Vector<3> position();
        
        void SetColor(Vector<3> color);
        Vector<3> color();

        void SetDirection(Vector<3> direction);
        Vector<3> direction();

        void SetAngleAttenuation(float attenuation);
        float angleAttenuation();

        void SetCutoffTheta(float cutoffTheta);
        float cutoffTheta();

    private:
        Vector<3> _position, _color, _direction;
        float _angleAttenuation, _cutoffTheta;
    };
}
