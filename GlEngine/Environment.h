#pragma once

#include "IPropertyProvider.h"

namespace GlEngine::ShaderFactory
{
    class ENGINE_SHARED Environment : public IPropertyProvider
    {
    private:
        Environment();
        ~Environment();

    public:
        static Environment &GetInstance();

        virtual std::vector<ShaderProp*> properties() override;
        
        virtual void Push(ShaderFactory &factory) override;

        float GetGameTime();

        void SetCameraPosition(Vector<3> position);
        Vector<3> cameraPosition() const;

    private:
        Vector<3> _cameraPos;
    };
}
