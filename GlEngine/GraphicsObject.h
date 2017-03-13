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

        void Render(RenderStage* stage) override;
        virtual void PreRender(RenderStage* stage);
        virtual void RenderImpl(RenderStage* stage) = 0;
        virtual void PostRender(RenderStage* stage);

        void RenderInstanced(RenderStage* stage, unsigned instanceCount);
        virtual void PreRenderInstanced(RenderStage* stage);
        virtual void RenderInstancedImpl(RenderStage* stage, unsigned instanceCount) = 0;
        virtual void PostRenderInstanced(RenderStage* stage);

        int renderOrder;

    protected:
        bool initialized, graphicsInitialized;

        std::vector<ShaderFactory::IPropertyProvider*> &providers();

    private:
        std::vector<ShaderFactory::IPropertyProvider*> _providers;
    };
}
