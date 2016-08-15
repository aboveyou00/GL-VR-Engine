#pragma once

#include "IGraphicsComponent.h"

namespace GlEngine
{
	namespace Impl
	{
		class GraphicsObjectImpl;
	}

	class ENGINE_SHARED GraphicsObject : public IGraphicsComponent
	{
	public:
		GraphicsObject(bool autoinit = true);
		~GraphicsObject();

        bool Initialize() override;
        void Shutdown() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

        void Render();
		virtual void PreRender();
        virtual void RenderImpl() = 0;
        virtual void PostRender();

        void RenderInstanced();
        virtual void PreRenderInstanced();
        virtual void RenderInstancedImpl();
        virtual void PostRenderInstanced();

    protected:
        bool initialized, graphicsInitialized;
	};
}
