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
        
        void SetScreenDimensions(Vector<2> dimensions);
        Vector<2> screenDimensions();

        void SetMouseScreenPosition(Vector<2> position);
        Vector<2> mouseScreenPosition();

        void SetMouseClipPosition(Vector<2> position);
        Vector<2> mouseClipPosition();

    private:
        Vector<3> _cameraPos;
        Vector<2> _screenDimensions;
        Vector<2> _mouseScreenPosition;
    };
}
