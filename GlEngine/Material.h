#pragma once

#include "IGraphicsComponent.h"
#include "IPropertyProvider.h"
#include "TesselationType.h"
#include "RenderTargetLayer.h"

namespace GlEngine
{
    class Texture;

    namespace ShaderFactory
    {
        class Attribute;
    }

    class ENGINE_SHARED Material : public IGraphicsComponent, public ShaderFactory::IPropertyProvider
    {
    public:
        Material(bool is2d = false);
        ~Material();

        virtual bool Initialize() override;
        virtual void Shutdown() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual bool IsOpaque() = 0;

        inline bool Is2d()
        {
            return is2d;
        }

        virtual RenderTargetLayer GetRenderTargetLayer();

        virtual TesselationType GetTesselationType() = 0;

        virtual std::vector<ShaderFactory::Attribute*> attributes() = 0;

    private:
        bool is2d;
    };
}
