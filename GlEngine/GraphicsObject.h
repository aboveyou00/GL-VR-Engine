#pragma once

#include "RenderTargetLayer.h"
#include "IPropertyProvider.h"
#include "GameComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class GraphicsObjectImpl;
    }

    class VaoFactory;

    class ENGINE_SHARED GraphicsObject : public GameComponent
    {
    public:
        GraphicsObject(std::string name, bool autoinit = true);
        ~GraphicsObject();

        bool InitializeAsync() override;
        void ShutdownAsync() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

        virtual void AddPropertyProvider(ShaderFactory::IPropertyProvider *provider);
        virtual void RemovePropertyProvider(ShaderFactory::IPropertyProvider *provider);

        virtual void BuildVao(VaoFactory &vao) = 0;

        void Render(RenderTargetLayer layer);
        virtual void PreRender(RenderTargetLayer layer);
        virtual void RenderImpl(RenderTargetLayer layer) = 0;
        virtual void PostRender(RenderTargetLayer layer);

        void RenderInstanced(RenderTargetLayer layer, unsigned instanceCount);
        virtual void PreRenderInstanced(RenderTargetLayer layer);
        virtual void RenderInstancedImpl(RenderTargetLayer layer, unsigned instanceCount) = 0;
        virtual void PostRenderInstanced(RenderTargetLayer layer);

        int renderOrder;

    protected:
        bool initialized, graphicsInitialized;

        void SetInstanceCount(unsigned count);

        std::vector<ShaderFactory::IPropertyProvider*> &providers();

    private:
        bool isInstanced;
        unsigned instanceCount;

        std::vector<ShaderFactory::IPropertyProvider*> _providers;
    };
}
