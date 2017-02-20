#pragma once

#include "IAsyncInitializable.h"
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

    class ENGINE_SHARED Material : public IAsyncInitializable, public ShaderFactory::IPropertyProvider
    {
    public:
        Material(std::string name, bool is2d = false);
        ~Material();

        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual bool isReady() override;

        virtual std::string name() override;

        virtual bool IsOpaque() = 0;

        inline bool Is2d()
        {
            return is2d;
        }

        virtual RenderTargetLayer GetRenderTargetLayer();

        virtual TesselationType GetTesselationType() = 0;

        virtual std::vector<ShaderFactory::Attribute*> attributes() = 0;

    private:
        std::string _name;
        bool is2d;
    };
}
