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
		GraphicsObject();
		~GraphicsObject();

        bool Initialize() override;
        void Shutdown() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

        virtual void Render();
		virtual void PreRender();
        virtual void RenderImpl() = 0;
        virtual void PostRender();

    protected:
        bool initialized, graphicsInitialized;
	};
}
